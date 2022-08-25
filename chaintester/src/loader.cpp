#include "loader.h"

fn_apply gApply = nullptr;

void SetApplyFn(fn_apply fn) {
    gApply = fn;
}

fn_apply GetApplyFn() {
    return gApply;
}


bool load_native_contract(const char *native_contract_path) {
    void *handle = dlopen(native_contract_path, RTLD_LAZY | RTLD_LOCAL);
    if (handle == 0) {
        printf("loading %s failed! error: %s\n", native_contract_path, dlerror());
        exit(-1);
        return false;
    }

    fn_native_init native_init = (fn_native_init)dlsym(handle, "native_init");
    if (native_init == nullptr) {
        printf("++++loading native_init failed! error: %s\n", dlerror());
        exit(-1);
        return false;
    }
    native_init(get_intrinsics());

    fn_native_apply native_apply = (fn_native_apply)dlsym(handle, "native_apply");
    if (native_apply == nullptr) {
        printf("++++loading native_apply failed! error: %s\n", dlerror());
        exit(-1);
        return false;
    }
    SetApplyFn(native_apply);
    return true;;
}