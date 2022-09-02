![build](https://github.com/uuosio/cpp-chaintester/actions/workflows/pr-any.yml/badge.svg?event=push)
[![codecov](https://codecov.io/gh/uuosio/cpp-chaintester/branch/main/graph/badge.svg?token=B1WQZRLLUI)](https://codecov.io/gh/uuosio/cpp-chaintester)

C++ test framework for EOS

# What is cpp-chaintester

1. It is a C++ test framework for EOS.
2. It makes writing C++ Smart Contracts test code more convenient.
3. It supports source-level C++ Smart Contracts debugging.
4. It supports generating code coverage for C++ Smart Contracts.

## How to Use

### Installing `ipyeos`
`cpp-chaintester` depends on `ipyeos` to run your test code.

Install it with the following command:

```bash
python3 -m pip install -U ipyeos
```

Then run the debugging server:

```bash
eos-debugger
```

Also, you can run eos-debugger in a docker container. Just follow the steps below.

```bash
docker pull ghcr.io/uuosio/ipyeos:latest
```

Run the debugging server on the Windows platform:

```bash
docker run -it --rm -p 9090:9090 -p 9092:9092 -t ghcr.io/uuosio/ipyeos
```

### Integrating cpp-chaintester with your project.

1. Add `cpp-chaintester` as a submodule of your project.

```
git submodule add https://github.com/uuosio/cpp-chaintester external/cpp-chaintester
```

2. Including it in your CMakeLists.txt for building `cpp-chaintester`

```
add_subdirectory(external/cpp-chaintester)
```


3. Writing your test.

4. There is a nice example project about how to use `cpp-chaintester` in your project.

[cpp-coverage-example](https://github.com/uuosio/cpp-coverage-example)
