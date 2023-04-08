export class Memory {
    private _memory: WebAssembly.Memory = null!;
    private _table: WebAssembly.Table = null!;
    private _alloc: (size: number) => number = () => 0;
    private _free: (ptr: number) => void = () => { };

    // The stored memory needs to be able to be changed after this object is created
    // This is because the WASM memory is exported from the module, but the imports need to be passed in before the exports can be grabbed
    setMemory(memory: WebAssembly.Memory) {
        this._memory = memory;
    }

    // The stored table needs to be able to be changed after this object is created
    // This is because the WASM table is exported from the module, but the imports need to be passed in before the exports can be grabbed
    setTable(table: WebAssembly.Table) {
        this._table = table;
    }

    setAllocateFns(alloc: (size: number) => number, free: (ptr: number) => void) {
        this._alloc = alloc;
        this._free = free;
    }

    allocWasmBuffer(len: number): number {
        return this._alloc(len);
    }

    allocWasmBufferWithData(buffer: ArrayBuffer): number {
        const len = buffer.byteLength;
        const ptr = this._alloc(len);
        new Uint8Array(this._memory.buffer, ptr, len).set(new Uint8Array(buffer));
        return ptr;
    }

    allocWasmString(str: string): number {
        const len = str.length;
        const ptr = this._alloc(len + 1); // + 1 for the terminating '\0'

        let data = new DataView(this._memory.buffer, ptr, len + 1);
        for (let i = 0; i < len; ++i) {
            data.setUint8(i, str.charCodeAt(i));
        }
        data.setUint8(len, 0);

        return ptr;
    }

    allocWasmArray(array: number[]): number {
        const sizeofPtr = 4;
        const size = sizeofPtr * array.length;
        const ptr = this.allocWasmBuffer(size);
        const view = new DataView(this._memory.buffer, ptr, size);

        for (const [i, ptr] of array.entries()) {
            view.setUint32(sizeofPtr * i, ptr, true);
        }

        return ptr;
    }

    freeWasmMemory(ptr: number): void {
        this._free(ptr);
    }

    createJsString(ptr: number): string {
        let len = 0;
        let data = new DataView(this._memory.buffer, ptr);
        while (data.getUint8(len) !== 0) {
            len += 1;
        }
        return this.createJsStringWithLength(ptr, len);
    }

    createJsStringWithLength(ptr: number, len: number): string {
        const decoder = new TextDecoder();
        return decoder.decode(this._memory.buffer.slice(ptr, ptr + len));
    }

    createJsBuffer(ptr: number, len?: number): ArrayBuffer {
        return this._memory.buffer.slice(ptr, len ? ptr + len : undefined);
    }

    createJsFunction(funcPtr: number): Function {
        return this._table.get(funcPtr);
    }
}
