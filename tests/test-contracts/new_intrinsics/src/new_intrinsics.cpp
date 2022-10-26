#include <new_intrinsics.hpp>
#include <eosio/system.hpp>
#include <eosio/action.hpp>
#include <eosio/crypto_ext.hpp>

extern "C" {
   __attribute__((eosio_wasm_import))
   uint32_t get_code_hash(eosio::name account, uint32_t struct_version, char* packed_result, uint32_t packed_result_len);

   __attribute__((eosio_wasm_import))
   void set_action_return_value(void *return_value, size_t size);

   __attribute__((eosio_wasm_import))
   uint32_t get_block_num();
}

struct get_code_hash_result {
   eosio::unsigned_int struct_version;
   uint64_t code_sequence;
   eosio::checksum256 code_hash;
   uint8_t vm_type;
   uint8_t vm_version;
   EOSLIB_SERIALIZE(get_code_hash_result, (struct_version)(code_sequence)(code_hash)(vm_type)(vm_version))
};

[[eosio::action]]
void new_intrinsics::test(uint32_t block_num) {
   eosio::check(block_num == get_block_num(), "bad block number");
   eosio::print_f("%", (uint32_t)get_block_num());
   set_action_return_value((void *)"helloworld", 10);

   auto hash = eosio::keccak("helloworld", 10);
   eosio::assert_keccak("helloworld", 10, hash);
   {
      std::vector<char> data(4+8+32+2);
      get_code_hash("hello"_n, 0, data.data(), data.size());
      auto ret = eosio::unpack<get_code_hash_result>(data);
      eosio::print_f("% % %\n", ret.code_sequence, ret.code_hash, ret.vm_type);
   }
}
