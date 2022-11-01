import os
import hashlib
import platform

from ipyeos import eos
from ipyeos import chaintester
from ipyeos.chaintester import ChainTester

chaintester.chain_config['contracts_console'] = True

def test_hello():
    eos.enable_debug(True)
    t = ChainTester(True)
    print(f'++++set breakpoint in hello.cpp and attach pid {os.getpid()} for debugging:')
    input('press Enter to continue...')
    with open('../build/tests/test-contracts/hello/hello/hello.wasm', 'rb') as f:
        code = f.read()
    with open('../build/tests/test-contracts/hello/hello/hello.abi', 'rb') as f:
        abi = f.read()
    t.deploy_contract('hello', code, abi)
    t.produce_block()
    t.chain.set_native_contract('hello', '../build/tests/test-contracts/hello/native/libhello_native_sharedd.dylib')

    t.push_action('hello', 'hi', {'nm': 'alice'}, {'hello': 'active'})
    t.produce_block()

    t.push_action('hello', 'check', {'nm': 'hello'}, {'hello': 'active'})
    t.produce_block()
