export function createTimeWasmImport() {
    return {
        "time": {
            "now": performance.now,
        },
    };
}
