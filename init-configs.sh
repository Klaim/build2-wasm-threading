rm -rf ../build-* .bdep/

bdep init -C ../build-clang @gcc cc --options-file config-gcc.options
bdep init -C ../build-clang @clang cc --options-file config-clang.options
bdep init -C ../build-wasm @wasm cc --options-file config-wasm.options



