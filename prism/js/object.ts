import { Memory } from "./memory";
import { RefMap } from "./ref_map";

export type JsAny = null | boolean | number | string | Object | HTMLElement | JsObject | Array<JsAny>;
export type JsObject = { [prop: string]: JsAny };
export class ObjectLibrary extends RefMap<JsAny> {

}

export function createObjectWasmImport(memory: Memory, objLib: ObjectLibrary) {
    return {
        "object": {
            "createNull": () => objLib.create(null),
            "createBoolean": (b: boolean) => objLib.create(b),
            "createNumber": (num: number) => objLib.create(num),
            "createString": (strPtr: number) => {
                const str = memory.createJsString(strPtr);
                return objLib.create(str);
            },
            "createObject": () => objLib.create({}),
            "createArray": () => objLib.create([]),
            "release": (id: number) => objLib.release(id),

            "parse": (strPtr: number) => {
                const str = memory.createJsString(strPtr);

                let value = null;
                try { value = JSON.parse(str); } catch (err) { }
                return objLib.create(value);
            },
            "stringify": (objId: number) => {
                let obj = objLib.get(objId);

                let value = "";
                try { value = JSON.stringify(obj); } catch (err) { }
                return memory.allocWasmString(value);
            },

            "isNull": (objId: number) => objLib.get(objId) == null,
            "isBoolean": (objId: number) => (typeof objLib.get(objId)) === "boolean",
            "isNumber": (objId: number) => (typeof objLib.get(objId)) === "number",
            "isString": (objId: number) => (typeof objLib.get(objId)) === "string",
            "isObject": (objId: number) => (typeof objLib.get(objId)) === "object" && !Array.isArray(objLib.get(objId)),
            "isArray": (objId: number) => Array.isArray(objLib.get(objId)),

            "asBoolean": (objId: number) => Boolean(objLib.get(objId)),
            "asNumber": (objId: number) => Number(objLib.get(objId)),
            "asString": (objId: number) => memory.allocWasmString(String(objLib.get(objId))),

            "has": (objId: number, propNamePtr: number) => {
                const propName = memory.createJsString(propNamePtr);
                try { return propName in (objLib.get(objId) as JsObject); } catch (err) { return false; }
            },
            "get": (objId: number, propNamePtr: number) => {
                const propName = memory.createJsString(propNamePtr);
                let value: JsAny = null;
                try { value = (objLib.get(objId) as JsObject)[propName]; } catch (err) { }
                return objLib.create(value);
            },

            "setNullProperty": (objId: number, propNamePtr: number) => {
                const propName = memory.createJsString(propNamePtr);
                try { (objLib.get(objId) as JsObject)[propName] = null; } catch (err) { }
            },
            "setBooleanProperty": (objId: number, propNamePtr: number, b: boolean) => {
                const propName = memory.createJsString(propNamePtr);
                try { (objLib.get(objId) as JsObject)[propName] = Boolean(b); } catch (err) { }
            },
            "setNumberProperty": (objId: number, propNamePtr: number, num: number) => {
                const propName = memory.createJsString(propNamePtr);
                try { (objLib.get(objId) as JsObject)[propName] = Number(num); } catch (err) { }
            },
            "setStringProperty": (objId: number, propNamePtr: number, strPtr: number) => {
                const propName = memory.createJsString(propNamePtr);
                const str = memory.createJsString(strPtr);
                try { (objLib.get(objId) as JsObject)[propName] = str; } catch (err) { }
            },
            "setObjectProperty": (objId: number, propNamePtr: number, valueObjId: number) => {
                const propName = memory.createJsString(propNamePtr);
                try { (objLib.get(objId) as JsObject)[propName] = objLib.get(valueObjId); } catch (err) { }
            },

            "equalsString": (objId: number, strPtr: number) => {
                const str = memory.createJsString(strPtr);
                return objLib.get(objId) === str;
            },

            "arrayPushObject": (objId: number, valueObjId: number) => {
                try { (objLib.get(objId) as Array<any>).push(objLib.get(valueObjId)); } catch (err) { }
            },
            "arrayLength": (objId: number) => {
                try { return (objLib.get(objId) as Array<any>).length; } catch (err) { return 0; }
            },
            "arrayPop": (objId: number) => { try { (objLib.get(objId) as Array<any>).pop(); } catch (err) { } },
            "arrayAt": (objId: number, index: number) => {
                let value = null;
                try { value = (objLib.get(objId) as Array<any>)[index]; } catch (err) { }
                return objLib.create(value);
            }
        },
    };
}
