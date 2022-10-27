//
// Copyright 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "zetasql/reference_impl/functions/range.h"

#include "zetasql/reference_impl/function.h"
#include "absl/types/span.h"

namespace zetasql {
namespace {

class RangeFunction : public SimpleBuiltinScalarFunction {
 public:
  explicit RangeFunction(const Type* output_type)
      : SimpleBuiltinScalarFunction(FunctionKind::kRangeCtor, output_type) {}
  absl::StatusOr<Value> Eval(absl::Span<const TupleData* const> params,
                             absl::Span<const Value> args,
                             EvaluationContext* context) const override;
};

absl::StatusOr<Value> RangeFunction::Eval(
    absl::Span<const TupleData* const> params, absl::Span<const Value> args,
    EvaluationContext* context) const {
  ZETASQL_RET_CHECK_EQ(args.size(), 2);
  ZETASQL_LOG(INFO) << "Making range: " << args[0].DebugString() << ", "
            << args[1].DebugString();
  ZETASQL_ASSIGN_OR_RETURN(Value range_value, Value::MakeRange(args[0], args[1]));

  return range_value;
}

}  // namespace

void RegisterBuiltinRangeFunctions() {
  BuiltinFunctionRegistry::RegisterScalarFunction(
      {FunctionKind::kRangeCtor},
      [](FunctionKind kind, const Type* output_type) {
        return new RangeFunction(output_type);
      });
}

}  // namespace zetasql