### Project Structure

``` 
-[src]
    -[include]
        - <common.hpp>
            - | GetProcessIdByName(LPCSTR processName) -> DWORD
            - | InjectDll(DWORD pid, LPCSTR dllPath)   -> DWORD

        - <hookbase.hpp>
            - | HOOK_install_Local(void** OriginFunc, void* HookedFunc) -> void
            - | HOOK_remove_local(void** OriginFunc, void* HookedFunc)  -> void
            - | HOOK_attach_LAUNCH_remote(LPCSTR lpApplicationPath, LPCSTR lpDllPath) -> DWORD
            - | HOOK_attach_EXISTED_remote(LPCSTR lpApplicationName, DWORD PID, LPCSTR dllPath) -> DWORD
```
