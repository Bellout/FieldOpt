
// -----------------------------------------------------------------
#include "constraint_handler.h"
#include <iostream>

// -----------------------------------------------------------------
namespace Optimization {
namespace Constraints {

// -----------------------------------------------------------------
ConstraintHandler::ConstraintHandler(
    QList<Settings::Optimizer::Constraint> constraints,
    Model::Properties::VariablePropertyContainer *variables,
    Reservoir::Grid::Grid *grid,
    Settings::Optimizer *settings) {

  // ---------------------------------------------------------------
  for (Settings::Optimizer::Constraint constraint : constraints) {

    // -------------------------------------------------------------
    switch (constraint.type) {

        // ---------------------------------------------------------
        // BHP
      case Settings::Optimizer::ConstraintType::BHP:
        constraints_.append(new BhpConstraint(constraint, variables));
        break;

        // ---------------------------------------------------------
        // RATE
      case Settings::Optimizer::ConstraintType::Rate:
        constraints_.append(new RateConstraint(constraint, variables));
        break;

        // ---------------------------------------------------------
        // WELL SPLINE LENGTH
      case Settings::Optimizer::ConstraintType::WellSplineLength:

        for (auto wname : constraint.wells) {
          auto cons = Settings::Optimizer::Constraint(constraint);
          cons.well = wname;
          constraints_.append(new WellSplineLength(cons, variables));
        }
        break;

        // -----------------------------------------------------------
        // WELL SPLINE INTERWELL DISTANCE
      case Settings::Optimizer::ConstraintType::WellSplineInterwellDistance:
        constraints_.append(new InterwellDistance(constraint, variables));
        break;

        // -----------------------------------------------------------
        // COMBINED WELL SPLINE LENGTH INTERWELL DISTANCE
      case Settings::Optimizer::ConstraintType::
        CombinedWellSplineLengthInterwellDistance:

        constraints_.append(
            new CombinedSplineLengthInterwellDistance(constraint, variables));
        break;

        // -----------------------------------------------------------
        // COMBINED WELL SPLINE LENGTH INTERWELL DISTANCE RES.BOUNDARY
      case Settings::Optimizer::ConstraintType::
        CombinedWellSplineLengthInterwellDistanceReservoirBoundary:

        constraints_.append(
            new CombinedSplineLengthInterwellDistanceReservoirBoundary(
                constraint, variables, grid));
        break;

        // -----------------------------------------------------------
        // RESERVOIR BOUNDARY
      case Settings::Optimizer::ConstraintType::ReservoirBoundary:

        for (auto wname : constraint.wells) {
          auto cons = Settings::Optimizer::Constraint(constraint);
          cons.well = wname;
          constraints_.append(new ReservoirBoundary(cons, variables, grid));
        }
        break;

        // -----------------------------------------------------------
        // PSEUDO CONTINUOUS BOUNDARY 2D
      case Settings::Optimizer::ConstraintType::PseudoContBoundary2D:

        for (auto wname : constraint.wells) {
          auto cons = Settings::Optimizer::Constraint(constraint);
          cons.well = wname;
          constraints_.append(new PseudoContBoundary2D(cons, variables, grid));
        }
        break;

#ifdef WITH_EXPERIMENTAL_CONSTRAINTS
        // Cases for constraints in the experimental_constraints directory go here
#endif

      default:
        break;
    }
  }

// ---------------------------------------------------------------
#ifdef WITH_EXPERIMENTAL_CONSTRAINTS
  std::cout << "Using experimental constraints" << std::endl;
#else
  std::cout << "Not using experimental constraints" << std::endl;
#endif
}

// ---------------------------------------------------------------
bool ConstraintHandler::CaseSatisfiesConstraints(Case *c) {

  // -------------------------------------------------------------
  // Check status wrt constraint, set to infeasible if true
  for (Constraint *constraint : constraints_) {
    if (!constraint->CaseSatisfiesConstraint(c)) {
      c->state.cons = Case::CaseState::ConsStatus::C_INFEASIBLE;
      return false;
    }
  }

  // -------------------------------------------------------------
  // Set status to feasible if not infeasible
  c->state.cons = Case::CaseState::ConsStatus::C_FEASIBLE;
  return true;
}

// ---------------------------------------------------------------
void ConstraintHandler::SnapCaseToConstraints(Case *c) {

  // -------------------------------------------------------------
  // For all constraint-types (associated with different subsets
  // of wells -- really?) apply each of the constraints sequentially
  // to the whole (!) real vector -> this is ok, since each constraint
  // type (i.e., the member.function SnapCaseToConstraints of each
  // constraint) operates on a different part of the real vector, e.g.,
  // BHP cosntraints and well placement constraints

  // This is an apparent sequentiality, though the real sequentiality
  // occurs at the level of each independent constraint type
  auto vec_before = c->GetRealVarVector();
  for (Constraint *constraint : constraints_) {
    constraint->SnapCaseToConstraints(c);
  }

  // -------------------------------------------------------------
  if (vec_before != c->GetRealVarVector()) {
    c->state.cons = Case::CaseState::ConsStatus::C_PROJECTED;
  }
  else {
    c->state.cons = Case::CaseState::ConsStatus::C_FEASIBLE;
  }

}

// ---------------------------------------------------------------
bool ConstraintHandler::HasBoundaryConstraints() const {

  // -------------------------------------------------------------
  for (auto con : constraints_) {
    if (con->IsBoundConstraint())
      return true;
  }
  return false;
}

// ---------------------------------------------------------------
Eigen::VectorXd
ConstraintHandler::GetLowerBounds(QList<QUuid> id_vector) const {

  // -------------------------------------------------------------
  Eigen::VectorXd lbounds(id_vector.size());
  lbounds.fill(0);
  for (auto con : constraints_) {
    if (con->IsBoundConstraint()) {
      lbounds = lbounds + con->GetLowerBounds(id_vector);
    }
  }
  return lbounds;
}

// ---------------------------------------------------------------
Eigen::VectorXd
ConstraintHandler::GetUpperBounds(QList<QUuid> id_vector) const {

  // -------------------------------------------------------------
  Eigen::VectorXd ubounds(id_vector.size());
  ubounds.fill(0);
  for (auto con : constraints_) {
    if (con->IsBoundConstraint()) {
      ubounds = ubounds + con->GetUpperBounds(id_vector);
    }
  }
  return ubounds;
}

// ---------------------------------------------------------------
void ConstraintHandler::InitializeNormalizers(QList<Case *> cases) {
  cout << "ConstraintHandler Initializing constraint normalizers" << endl;
  for (auto con : constraints_) {
    con->InitializeNormalizer(cases);
  }
}

// ---------------------------------------------------------------
long double
ConstraintHandler::GetWeightedNormalizedPenalties(Case *c) {

  long double wnp = 0.0L;
  for (auto con : constraints_) {
    long double pen = con->PenaltyNormalized(c);
    wnp += pen * con->GetPenaltyWeight();
  }
  return wnp;
}

long double ConstraintHandler::GetWeightedLengthPenalties(Case *c) {
    long double wnp = 0.0L;
    for (auto con : constraints_) {
        long double pen = con->PenaltyNormalized(c);
        wnp += pen * con->GetPenaltyWeight();
    }
    return wnp;
}


}
}
