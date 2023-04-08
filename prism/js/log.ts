import { Memory } from "./memory";

export function createConsoleWasmImport(memory: Memory) {
    return {
        "console": {
            "log": (strPtr: number) => console.log(memory.createJsString(strPtr)),
            "error": (strPtr: number) => console.error(memory.createJsString(strPtr)),
        },
    };
}
