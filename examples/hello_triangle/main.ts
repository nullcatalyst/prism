import * as prism from "@com_nullcatalyst_prism/prism";

interface WasmExports {
    memory: WebAssembly.Memory;
    __indirect_function_table: WebAssembly.Table;

    memAlloc: (size: number) => number;
    memFree: (ptr: number) => void;
    init: () => void;
    start: () => void;
    render: () => void;
}

(async () => {
    const url = "hello_triangle.wasm";
    const memory = new prism.Memory();
    const objLib = new prism.ObjectLibrary();

    const gpuDevice = await prism.getWebgpuDevice();

    const { module, instance } = await WebAssembly.instantiateStreaming(fetch(url), {
        "env": {
            "abort": () => { throw new Error("aborted"); },
        },
        ...prism.createMathWasmImport(),
        ...prism.createConsoleWasmImport(memory),
        ...prism.createObjectWasmImport(memory, objLib),
        ...prism.createDomWasmImport(memory, objLib),
        ...prism.createGpuWasmImport(gpuDevice, memory, objLib),
    });

    const wasmExports = instance.exports as any as WasmExports;

    memory.setMemory(wasmExports["memory"]);
    memory.setTable(wasmExports["__indirect_function_table"]);
    memory.setAllocateFns(wasmExports["memAlloc"], wasmExports["memFree"]);

    wasmExports["init"]();

    const render = wasmExports["render"];
    function nextFrame() {
        render();
        requestAnimationFrame(nextFrame);
    }
    requestAnimationFrame(nextFrame);
})();
