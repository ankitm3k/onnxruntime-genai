#pragma once
#include "model.h"
#include "input_ids.h"
#include "logits.h"
#include "kv_cache.h"
#include "position_ids.h"

namespace Generators {

struct Mistral_Model : Model {
  Mistral_Model(std::unique_ptr<Config> config, OrtEnv& ort_env, const ProviderOptions* provider_options);

  std::unique_ptr<State> CreateState(RoamingArray<int32_t> sequence_lengths, const SearchParams& params) override;

  std::unique_ptr<OrtSession> session_decoder_;
};

struct Mistral_State : State {
  Mistral_State(Mistral_Model& model, RoamingArray<int32_t> sequence_lengths, const SearchParams& params);
  RoamingArray<float> Run(int current_length, RoamingArray<int32_t> next_tokens, RoamingArray<int32_t> next_indices) override;

 private:
  void UpdateInputs(RoamingArray<int32_t> next_tokens, RoamingArray<int32_t> next_indices, int current_length);

  Mistral_Model& model_;
  bool first_run_{true};

  InputIDs<int64_t> input_ids_{model_, *this};
  Logits logits_{model_, *this};
  KV_Cache kv_cache_{model_, *this};
  PositionIDs<int64_t> position_ids_;
};

}  // namespace Generators