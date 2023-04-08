export function createMathWasmImport() {
    return {
        "math": {
            "log": Math.log,
            "exp": Math.exp,
            "sqrt": Math.sqrt,
            "sin": Math.sin,
            "cos": Math.cos,
            "tan": Math.tan,
            "atan2": Math.atan2,
        },
    };
}
