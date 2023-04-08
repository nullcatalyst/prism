import { Memory } from "./memory";
import { getKeyCode } from "./keycode";
import { ObjectLibrary } from "./object";

export function createDomWasmImport(memory: Memory, objLib: ObjectLibrary) {
    return {
        "dom": {
            "getById": (domIdPtr: number) => {
                const str = memory.createJsString(domIdPtr);
                return objLib.create(document.getElementById(str) as HTMLElement);
            },
            "onMouseMoved": (elemId: number, callbackPtr: number, userDataPtr: number) => {
                const elem = objLib.get(elemId) as HTMLElement;
                const callback = memory.createJsFunction(callbackPtr);
                elem.addEventListener("mousemove", event => {
                    const rect = elem.getBoundingClientRect();
                    const x = event.clientX - rect.left;
                    const y = event.clientY - rect.top;
                    callback(x, y, userDataPtr);
                });
            },
            "onMouseButtonDown": (elemId: number, callbackPtr: number, userDataPtr: number) => {
                const elem = objLib.get(elemId) as HTMLElement;
                const callback = memory.createJsFunction(callbackPtr);
                elem.addEventListener("mousedown", event => {
                    // `.button+1` to match the button numbers in the C++ code, where 0 is used as an invalid value
                    callback(event.button + 1, userDataPtr);
                });
            },
            "onMouseButtonUp": (elemId: number, callbackPtr: number, userDataPtr: number) => {
                const elem = objLib.get(elemId) as HTMLElement;
                const callback = memory.createJsFunction(callbackPtr);
                elem.addEventListener("mouseup", event => {
                    // `.button+1` to match the button numbers in the C++ code, where 0 is used as an invalid value
                    callback(event.button + 1, userDataPtr);
                });
            },
            "onKeyDown": (elemId: number, callbackPtr: number, userDataPtr: number) => {
                const elem = objLib.get(elemId) as HTMLElement;
                const callback = memory.createJsFunction(callbackPtr);
                elem.addEventListener("keydown", event => {
                    // `.button+1` to match the button numbers in the C++ code, where 0 is used as an invalid value
                    callback(getKeyCode(event), userDataPtr);
                });
            },
            "onKeyUp": (elemId: number, callbackPtr: number, userDataPtr: number) => {
                const elem = objLib.get(elemId) as HTMLElement;
                const callback = memory.createJsFunction(callbackPtr);
                elem.addEventListener("keyup", event => {
                    // `.button+1` to match the button numbers in the C++ code, where 0 is used as an invalid value
                    callback(getKeyCode(event), userDataPtr);
                });
            },
        },
    };
}
