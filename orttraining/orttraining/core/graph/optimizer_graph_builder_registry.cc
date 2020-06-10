// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "orttraining/core/graph/optimizer_graph_builder_registry.h"

// optimizer graph builders to register
#include "orttraining/core/graph/optimizer_graph_builder.h"
#include "orttraining/core/graph/allreduce_optimizer_graph_builder.h"
#include "orttraining/core/graph/zero_optimizer_graph_builder.h"
#include "orttraining/core/graph/adasum_optimizer_graph_builder.h"

namespace onnxruntime {
namespace training {

// Register all optimizer graph builders here.
void OptimizerGraphBuilderRegistry::RegisterGraphBuilders() {
  GetInstance().Register<OptimizerGraphBuilder>("Default");
  GetInstance().Register<AllreduceOptimizerGraphBuilder>("Allreduce");
  GetInstance().Register<ZeROOptimizerGraphBuilder>("ZeRO");
  GetInstance().Register<AdasumOptimizerGraphBuilder>("Adasum");
}

std::string OptimizerGraphBuilderRegistry::GetNameFromConfig(const OptimizerGraphConfig& config) const {
  if (config.data_parallel_group_size > 1) {
    if (config.partition_optimizer) {
      std::cout << "Using optimizer graph builder ZeRO\n";
      return "ZeRO";
    } else if (config.adasum_reduction_type != AdasumReductionType::None) {
      std::cout << "Using optimizer graph builder Adasum\n";
      return "Adasum";
    } else {
      std::cout << "Using optimizer graph builder Allreduce\n";
      return "Allreduce";
    }
  }

  std::cout << "Using optimizer graph builder Default\n";
  return "Default";
}

}  // namespace training
}  // namespace onnxruntime
