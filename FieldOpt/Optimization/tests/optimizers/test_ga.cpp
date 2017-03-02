
#include <gtest/gtest.h>
#include "Optimization/optimizers/GeneticAlgorithm.h"
#include "Optimization/tests/test_resource_optimizer.h"
#include "Reservoir/tests/test_resource_grids.h"
#include "Optimization/tests/test_resource_test_functions.h"

using namespace TestResources::TestFunctions;
using namespace Optimization::Optimizers;

namespace {

class GeneticAlgorithmTest : public ::testing::Test,
                          public TestResources::TestResourceOptimizer,
                          public TestResources::TestResourceGrids {
 protected:
  GeneticAlgorithmTest() {
      base_ = base_case_;
  }
  virtual ~GeneticAlgorithmTest() {}
  virtual void SetUp() {}

  Optimization::Case *base_;

};

TEST_F(GeneticAlgorithmTest, Constructor) {
}

TEST_F(GeneticAlgorithmTest, TestFunctionSpherical) {
    test_case_2r_->set_objective_function_value(Sphere(test_case_2r_->GetRealVarVector()));
    Optimization::Optimizer *minimizer = new GeneticAlgorithm(settings_ga_min_,
                                                           test_case_2r_, varcont_prod_bhp_, grid_5spot_);

    while (!minimizer->IsFinished()) {
        auto next_case = minimizer->GetCaseForEvaluation();
        next_case->set_objective_function_value(Sphere(next_case->GetRealVarVector()));
        minimizer->SubmitEvaluatedCase(next_case);
    }
    auto best_case = minimizer->GetTentativeBestCase();
    EXPECT_NEAR(0.0, best_case->objective_function_value(), 0.01);
    EXPECT_NEAR(0.0, best_case->GetRealVarVector()[0], 0.01);
    EXPECT_NEAR(0.0, best_case->GetRealVarVector()[1], 0.01);
}

TEST_F(GeneticAlgorithmTest, TestFunctionRosenbrock) {

    // First test the Rosenbrock function itself
    Eigen::VectorXd optimum(2); optimum << 1.0, 1.0;
    EXPECT_FLOAT_EQ(0.0, Rosenbrock(optimum));

    test_case_2r_->set_objective_function_value(Rosenbrock(test_case_2r_->GetRealVarVector()));
    Optimization::Optimizer *minimizer = new GeneticAlgorithm(settings_ga_min_,
                                                           test_case_2r_, varcont_prod_bhp_, grid_5spot_);

    while (!minimizer->IsFinished()) {
        auto next_case = minimizer->GetCaseForEvaluation();
        next_case->set_objective_function_value(Rosenbrock(next_case->GetRealVarVector()));
        minimizer->SubmitEvaluatedCase(next_case);
    }
    auto best_case = minimizer->GetTentativeBestCase();

    EXPECT_NEAR(0.0, best_case->objective_function_value(), 5);
    EXPECT_NEAR(1.0, best_case->GetRealVarVector()[0], 2.5);
    EXPECT_NEAR(1.0, best_case->GetRealVarVector()[1], 2.5);
}

}
