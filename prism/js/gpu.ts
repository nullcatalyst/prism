import { Memory } from "./memory";
import { JsObject, ObjectLibrary } from "./object";
import { RefMap } from "./ref_map";

import "./webgpu.typings";

export async function getWebgpuDevice(): Promise<GPUDevice> {
    const navGpu = navigator.gpu;
    if (navGpu == null) {
        throw new Error("WebGPU is not supported on this browser");
    }

    const adapter = await navGpu.requestAdapter();
    if (adapter == null) {
        throw new Error("failed to get WebGPU hardware adapter");
    }

    return adapter.requestDevice();
}

const textureFormats /*: { [name in GPUTextureFormat]: number }*/ = {
    "r8unorm": 0x00000001,
    "r8snorm": 0x00000002,
    "r8uint": 0x00000003,
    "r8sint": 0x00000004,
    "r16uint": 0x00000005,
    "r16sint": 0x00000006,
    "r16float": 0x00000007,
    "rg8unorm": 0x00000008,
    "rg8snorm": 0x00000009,
    "rg8uint": 0x0000000A,
    "rg8sint": 0x0000000B,
    "r32float": 0x0000000C,
    "r32uint": 0x0000000D,
    "r32sint": 0x0000000E,
    "rg16uint": 0x0000000F,
    "rg16sint": 0x00000010,
    "rg16float": 0x00000011,
    "rgba8unorm": 0x00000012,
    "rgba8unorm-srgb": 0x00000013,
    "rgba8snorm": 0x00000014,
    "rgba8uint": 0x00000015,
    "rgba8sint": 0x00000016,
    "bgra8unorm": 0x00000017,
    "bgra8unorm-srgb": 0x00000018,
    // "rgb10a2unorm": 0x00000019,
    // "rg11b10ufloat": 0x0000001A,
    // "rgb9e5ufloat": 0x0000001B,
    "rg32float": 0x0000001C,
    "rg32uint": 0x0000001D,
    "rg32sint": 0x0000001E,
    "rgba16uint": 0x0000001F,
    "rgba16sint": 0x00000020,
    "rgba16float": 0x00000021,
    "rgba32float": 0x00000022,
    "rgba32uint": 0x00000023,
    "rgba32sint": 0x00000024,
    "depth16unorm": 0x00000026,
    "depth32float": 0x00000029,
};

export class Context {
    private _device: GPUDevice = null!;
    private _context: GPUCanvasContext = null!;
    private _drawEncoder: GPUCommandEncoder = null!;

    private readonly _bindGroupLayouts = new RefMap<GPUBindGroupLayout>();
    private readonly _bindGroups = new RefMap<GPUBindGroup>();
    private readonly _shaderModules = new RefMap<GPUShaderModule>();
    private readonly _pipelineLayouts = new RefMap<GPUPipelineLayout>();
    private readonly _pipelines = new RefMap<GPURenderPipeline>();
    private readonly _buffers = new RefMap<GPUBuffer>();
    private readonly _textures = new RefMap<GPUTexture>();
    private readonly _textureViews = new RefMap<GPUTextureView>();
    private readonly _samplers = new RefMap<GPUSampler>();
    private readonly _renderPasses = new RefMap<GPURenderPassEncoder>();

    private readonly _surfaceFormat: GPUTextureFormat;

    // TODO: At this time, it appears that chrome does not support sRGB, even though the spec says
    // it's required to support the format: "bgra8unorm-srgb", which would be the better default.
    constructor(device: GPUDevice, canvas: HTMLCanvasElement, surfaceFormat: GPUTextureFormat = "bgra8unorm") {
        const devicePixelRatio = (window.devicePixelRatio || 1);
        const clientWidth = canvas.clientWidth;
        const clientHeight = canvas.clientHeight;
        canvas.style.width = `${clientWidth / devicePixelRatio}px`;
        canvas.style.height = `${clientHeight / devicePixelRatio}px`;


        const context = canvas.getContext("webgpu");
        if (context == null) {
            throw new Error("failed to get WebGPU canvas context");
        }
        context.configure({
            "device": device,
            "format": surfaceFormat,
            "alphaMode": "opaque",
        });

        this._device = device;
        this._context = context;
        this._surfaceFormat = surfaceFormat;
    }

    getSurfaceFormat() {
        return this._surfaceFormat;
    }

    resize(width: number, height: number) {
        const canvas = this._context.canvas as HTMLCanvasElement;
        canvas.width = width;
        canvas.height = height;
    }

    createBindGroupLayout(desc: GPUBindGroupLayoutDescriptor) {
        return this._bindGroupLayouts.create(this._device.createBindGroupLayout(desc));
    }

    createBindGroup(desc: GPUBindGroupDescriptor) {
        return this._bindGroups.create(this._device.createBindGroup(desc));
    }

    createShaderModule(source: string) {
        return this._shaderModules.create(this._device.createShaderModule({
            "code": source,//document.getElementById(sourceUrl)!.innerText,
        }));
    }

    createPipelineLayout(desc: GPUPipelineLayoutDescriptor) {
        return this._pipelineLayouts.create(this._device.createPipelineLayout(desc));
    }

    createRenderPipeline(desc: GPURenderPipelineDescriptor) {
        return this._pipelines.create(this._device.createRenderPipeline(desc));
    }

    createBuffer(usage: GPUBufferUsageFlags, bufferSize: number, data: ArrayBuffer, dataOffsetIntoBuffer: number) {
        const copy = data.byteLength > 0;
        const buffer = this._device.createBuffer({
            "usage": usage,
            "size": bufferSize,
            "mappedAtCreation": copy,
        });
        if (copy) {
            const writeArray = new Uint8Array(buffer.getMappedRange());
            writeArray.set(new Uint8Array(data), dataOffsetIntoBuffer);
            buffer.unmap();
        }
        return this._buffers.create(buffer);
    }

    updateBuffer(bufferId: number, data: ArrayBuffer, dataOffsetIntoBuffer: number) {
        this._device.queue.writeBuffer(this._buffers.get(bufferId), dataOffsetIntoBuffer, data);
    }

    createTexture2d(usage: number, format: GPUTextureFormat, width: number, height: number) {
        return this._textures.create(this._device.createTexture({
            "dimension": "2d",
            "usage": usage,
            "format": format,
            "size": {
                "width": width,
                "height": height,
                "depthOrArrayLayers": 1,
            },
        }));
    }

    updateTexture2d(textureId: number, width: number, height: number, data: ArrayBuffer) {
        this._device.queue.writeTexture({
            "texture": this._textures.get(textureId),
            "mipLevel": 0,
            "origin": {
                "x": 0,
                "y": 0,
                "z": 0,
            },
            "aspect": "all",
        }, data, {
            "offset": 0,
            "bytesPerRow": data.byteLength / height,
            "rowsPerImage": height,
        }, {
            "width": width,
            "height": height,
            "depthOrArrayLayers": 1,
        });
    }

    createTextureView2d(textureId: number, format: GPUTextureFormat) {
        return this._textureViews.create(this._textures.get(textureId).createView({
            "dimension": "2d",
            "format": format,
            "baseMipLevel": 0,
            "mipLevelCount": 1,
            "baseArrayLayer": 0,
            "arrayLayerCount": 1,
            "aspect": "all",
        }));
    }

    createSampler(addressMode: GPUAddressMode, minFilter: GPUFilterMode, magFilter: GPUFilterMode, mipmapFilter: GPUFilterMode) {
        return this._samplers.create(this._device.createSampler({
            "addressModeU": addressMode,
            "addressModeV": addressMode,
            "addressModeW": addressMode,
            "magFilter": magFilter,
            "minFilter": minFilter,
            "mipmapFilter": mipmapFilter,
            // "lodMinClamp": 0,
            // "lodMaxClamp": 0,
            // "compare": "always",
            // "maxAnisotropy": 0,
        }));
    }

    createSamplerComparison(compare: GPUCompareFunction, addressMode: GPUAddressMode, minFilter: GPUFilterMode, magFilter: GPUFilterMode, mipmapFilter: GPUFilterMode) {
        return this._samplers.create(this._device.createSampler({
            "addressModeU": addressMode,
            "addressModeV": addressMode,
            "addressModeW": addressMode,
            "magFilter": magFilter,
            "minFilter": minFilter,
            "mipmapFilter": mipmapFilter,
            // "lodMinClamp": 0,
            // "lodMaxClamp": 0,
            "compare": compare,
            // "maxAnisotropy": 0,
        }));
    }

    ////////////////////////////////
    // Render pass
    beginRenderPass(desc: GPURenderPassDescriptor, x: number, y: number, width: number, height: number) {
        const passEncoder = this._drawEncoder.beginRenderPass(desc);
        passEncoder.setViewport(x, y, width, height, 0, 1);
        passEncoder.setScissorRect(x, y, width, height);
        return this._renderPasses.create(passEncoder);
    }
    endRenderPass(renderPassId: number) { this._renderPasses.get(renderPassId).end(); }
    setPipeline(renderPassId: number, pipelineId: number) { this._renderPasses.get(renderPassId).setPipeline(this._pipelines.get(pipelineId)); }
    setBindGroup(renderPassId: number, slot: number, bindGroupId: number) { this._renderPasses.get(renderPassId).setBindGroup(slot, this._bindGroups.get(bindGroupId)); }
    setBuffer(renderPassId: number, slot: number, bufferId: number, offset: number) { this._renderPasses.get(renderPassId).setVertexBuffer(slot, this._buffers.get(bufferId), offset); }
    setIndexU16Buffer(renderPassId: number, bufferId: number, offset: number, size: number) { this._renderPasses.get(renderPassId).setIndexBuffer(this._buffers.get(bufferId), "uint16", offset, size >= 0 ? size : undefined); }
    setIndexU32Buffer(renderPassId: number, bufferId: number, offset: number, size: number) { this._renderPasses.get(renderPassId).setIndexBuffer(this._buffers.get(bufferId), "uint32", offset, size >= 0 ? size : undefined); }
    draw(renderPassId: number, vertexCount: number, instanceCount: number, firstVertex: number, firstInstance: number) { this._renderPasses.get(renderPassId).draw(vertexCount, instanceCount, firstVertex, firstInstance); }
    drawIndexed(renderPassId: number, indexCount: number, instanceCount: number, firstIndex: number, baseVertex: number, firstInstance: number) { this._renderPasses.get(renderPassId).drawIndexed(indexCount, instanceCount, firstIndex, baseVertex, firstInstance); }
    drawIndirect(renderPassId: number, bufferId: number, indirectOffset: number) { this._renderPasses.get(renderPassId).drawIndirect(this._buffers.get(bufferId), indirectOffset); }
    drawIndexedIndirect(renderPassId: number, bufferId: number, indirectOffset: number) { this._renderPasses.get(renderPassId).drawIndexedIndirect(this._buffers.get(bufferId), indirectOffset); }

    startFrame() { this._drawEncoder = this._device.createCommandEncoder(); }
    presentFrame() { this._device.queue.submit([this._drawEncoder.finish()]); }
    getSwapChainView() { return this._textureViews.create(this._context.getCurrentTexture().createView()); }


    ////////////////////////////////
    // Getters
    getBindGroupLayout(bindGroupLayoutId: number) { return this._bindGroupLayouts.get(bindGroupLayoutId); }
    getBindGroup(bindGroupId: number) { return this._bindGroups.get(bindGroupId); }
    getShaderModule(shaderModuleId: number) { return this._shaderModules.get(shaderModuleId); }
    getPipelineLayout(pipelineLayoutId: number) { return this._pipelineLayouts.get(pipelineLayoutId); }
    getPipeline(pipelineId: number) { return this._pipelines.get(pipelineId); }
    getBuffer(bufferId: number) { return this._buffers.get(bufferId); }
    getTexture(textureId: number) { return this._textures.get(textureId); }
    getTextureView(textureViewId: number) { return this._textureViews.get(textureViewId); }
    getSampler(samplerId: number) { return this._samplers.get(samplerId); }
    getRenderPass(renderPassId: number) { return this._renderPasses.get(renderPassId); }


    ////////////////////////////////
    // Releasers
    releaseBindGroupLayout(bindGroupLayoutId: number) { this._bindGroupLayouts.release(bindGroupLayoutId); }
    releaseBindGroup(bindGroupId: number) { this._bindGroups.release(bindGroupId); }
    releaseShaderModule(shaderModuleId: number) { this._shaderModules.release(shaderModuleId); }
    releasePipelineLayout(pipelineLayoutId: number) { this._pipelineLayouts.release(pipelineLayoutId); }
    releasePipeline(pipelineId: number) { this._pipelines.release(pipelineId); }
    releaseBuffer(bufferId: number) { this._buffers.release(bufferId); }
    releaseTexture(textureId: number) { this._textures.release(textureId); }
    releaseTextureView(textureViewId: number) { this._textureViews.release(textureViewId); }
    releaseSampler(samplerId: number) { this._samplers.release(samplerId); }
    releaseRenderPass(renderPassId: number) { this._renderPasses.release(renderPassId); }
}

export function createGpuWasmImport(gpuDevice: GPUDevice, memory: Memory, objLib: ObjectLibrary) {
    function createSetObjectPropertyFromContextValue(getter: (ctx: Context, value: number) => any) {
        return (ctxObjId: number, objId: number, namePtr: number, value: number) => {
            const ctx = objLib.get(ctxObjId) as Context;
            const valueObj = getter(ctx, value);
            if (namePtr === 0) {
                // If the name is null, then the object must be an array that we are pushing onto
                (objLib.get(objId) as any[]).push(valueObj);
            } else {
                (objLib.get(objId) as JsObject)[memory.createJsString(namePtr)] = valueObj;
            }
        };
    }

    return {
        "gpu": {
            "getPixelRatio": () => window.devicePixelRatio,
            "getSurfaceFormat": (ctxObjId: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                // Not all formats supported by the browser are currently supported by us, so we
                // need to do a cast to appease the type checker.
                const format = ctx.getSurfaceFormat() as keyof typeof textureFormats;
                return textureFormats[format] || 0;
            },

            "createContext": (canvasObjId: number) => {
                const canvas = objLib.get(canvasObjId) as HTMLCanvasElement;
                if (!(canvas instanceof HTMLCanvasElement)) {
                    throw new Error("cannot create a gpu context from a non-canvas object");
                }
                return objLib.create(new Context(gpuDevice, canvas));
            },
            "createBindGroupLayout": (ctxObjId: number, descObjId: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                const desc = objLib.get(descObjId) as GPUBindGroupLayoutDescriptor;
                return ctx.createBindGroupLayout(desc);
            },
            "createBindGroup": (ctxObjId: number, descObjId: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                const desc = objLib.get(descObjId) as GPUBindGroupDescriptor;
                return ctx.createBindGroup(desc);
            },
            "createShaderModule": (ctxObjId: number, sourcePtr: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                const source = memory.createJsString(sourcePtr);
                return ctx.createShaderModule(source);
            },
            "createPipelineLayout": (ctxObjId: number, descObjId: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                const desc = objLib.get(descObjId) as GPUPipelineLayoutDescriptor;
                return ctx.createPipelineLayout(desc);
            },
            "createRenderPipeline": (ctxObjId: number, descObjId: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                const desc = objLib.get(descObjId) as GPURenderPipelineDescriptor;
                return ctx.createRenderPipeline(desc);
            },
            "createBuffer": (ctxObjId: number, usage: number, bufferSize: number, dataPtr: number, dataSize: number, dataOffsetIntoBuffer: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                const data = memory.createJsBuffer(dataPtr, dataSize >= 0 ? dataSize : undefined);
                return ctx.createBuffer(usage, bufferSize, data, dataOffsetIntoBuffer);
            },
            "updateBuffer": (ctxObjId: number, bufferId: number, dataPtr: number, dataSize: number, dataOffsetIntoBuffer: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                const data = memory.createJsBuffer(dataPtr, dataSize);
                ctx.updateBuffer(bufferId, data, dataOffsetIntoBuffer);
            },
            "createTexture2d": (ctxObjId: number, usage: number, formatStrPtr: number, width: number, height: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                const format = memory.createJsString(formatStrPtr) as GPUTextureFormat;
                return ctx.createTexture2d(usage, format, width, height);
            },
            "updateTexture2d": (ctxObjId: number, textureId: number, width: number, height: number, dataPtr: number, dataSize: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                const data = memory.createJsBuffer(dataPtr, dataSize);
                ctx.updateTexture2d(textureId, width, height, data);
            },
            "createTextureView2d": (ctxObjId: number, textureId: number, formatStrPtr: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                const format = memory.createJsString(formatStrPtr) as GPUTextureFormat;
                return ctx.createTextureView2d(textureId, format);
            },
            "createSampler": (ctxObjId: number, addressModeStrPtr: number, minFilterStrPtr: number, magFilterStrPtr: number, mipmapFilterStrPtr: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                const addressMode = memory.createJsString(addressModeStrPtr) as GPUAddressMode;
                const minFilter = memory.createJsString(minFilterStrPtr) as GPUFilterMode;
                const magFilter = memory.createJsString(magFilterStrPtr) as GPUFilterMode;
                const mipmapFilter = memory.createJsString(mipmapFilterStrPtr) as GPUFilterMode;
                return ctx.createSampler(addressMode, minFilter, magFilter, mipmapFilter);
            },
            "createSamplerComparison": (ctxObjId: number, compareStrPtr: number, addressModeStrPtr: number, minFilterStrPtr: number, magFilterStrPtr: number, mipmapFilterStrPtr: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                const compare = memory.createJsString(compareStrPtr) as GPUCompareFunction;
                const addressMode = memory.createJsString(addressModeStrPtr) as GPUAddressMode;
                const minFilter = memory.createJsString(minFilterStrPtr) as GPUFilterMode;
                const magFilter = memory.createJsString(magFilterStrPtr) as GPUFilterMode;
                const mipmapFilter = memory.createJsString(mipmapFilterStrPtr) as GPUFilterMode;
                return ctx.createSamplerComparison(compare, addressMode, minFilter, magFilter, mipmapFilter);
            },

            "getSwapChainView": (ctxObjId: number) => (objLib.get(ctxObjId) as Context).getSwapChainView(),
            "startFrame": (ctxObjId: number) => (objLib.get(ctxObjId) as Context).startFrame(),
            "presentFrame": (ctxObjId: number) => (objLib.get(ctxObjId) as Context).presentFrame(),

            ////////////////////////////////
            // Render pass
            "beginRenderPass": (ctxObjId: number, descObjId: number, width: number, height: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                const desc = objLib.get(descObjId) as GPURenderPassDescriptor;
                return ctx.beginRenderPass(desc, width, height);
            },
            "endRenderPass": (ctxObjId: number, renderPassId: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                ctx.endRenderPass(renderPassId);
            },
            "setPipeline": (ctxObjId: number, renderPassId: number, pipelineId: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                ctx.setPipeline(renderPassId, pipelineId);
            },
            "setBindGroup": (ctxObjId: number, renderPassId: number, slot: number, bindGroupId: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                ctx.setBindGroup(renderPassId, slot, bindGroupId);
            },
            "setBuffer": (ctxObjId: number, renderPassId: number, slot: number, bufferId: number, offset: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                ctx.setBuffer(renderPassId, slot, bufferId, offset);
            },
            "setIndexU16Buffer": (ctxObjId: number, renderPassId: number, bufferId: number, offset: number, size: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                ctx.setIndexU16Buffer(renderPassId, bufferId, offset, size);
            },
            "setIndexU32Buffer": (ctxObjId: number, renderPassId: number, bufferId: number, offset: number, size: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                ctx.setIndexU32Buffer(renderPassId, bufferId, offset, size);
            },

            "draw": (ctxObjId: number, renderPassId: number, vertexCount: number, instanceCount: number, firstVertex: number, firstInstance: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                ctx.draw(renderPassId, vertexCount, instanceCount, firstVertex, firstInstance);
            },
            "drawIndexed": (ctxObjId: number, renderPassId: number, indexCount: number, instanceCount: number, firstIndex: number, baseVertex: number, firstInstance: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                ctx.drawIndexed(renderPassId, indexCount, instanceCount, firstIndex, baseVertex, firstInstance);
            },
            "drawIndirect": (ctxObjId: number, renderPassId: number, indirectBufferId: number, indirectOffset: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                ctx.drawIndirect(renderPassId, indirectBufferId, indirectOffset);
            },
            "drawIndexedIndirect": (ctxObjId: number, renderPassId: number, indirectBufferId: number, indirectOffset: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                ctx.drawIndexedIndirect(renderPassId, indirectBufferId, indirectOffset);
            },

            ////////////////////////////////
            // Set object property to GPU resource
            "setObjectBindGroupLayoutProperty": createSetObjectPropertyFromContextValue((ctx, id) => ctx.getBindGroupLayout(id)),
            "setObjectBindGroupProperty": createSetObjectPropertyFromContextValue((ctx, id) => ctx.getBindGroup(id)),
            "setObjectShaderModuleProperty": createSetObjectPropertyFromContextValue((ctx, id) => ctx.getShaderModule(id)),
            "setObjectPipelineLayoutProperty": createSetObjectPropertyFromContextValue((ctx, id) => ctx.getPipelineLayout(id)),
            "setObjectPipelineProperty": createSetObjectPropertyFromContextValue((ctx, id) => ctx.getPipeline(id)),
            "setObjectBufferProperty": createSetObjectPropertyFromContextValue((ctx, id) => ctx.getBuffer(id)),
            "setObjectTextureProperty": createSetObjectPropertyFromContextValue((ctx, id) => ctx.getTexture(id)),
            "setObjectTextureViewProperty": createSetObjectPropertyFromContextValue((ctx, id) => ctx.getTextureView(id)),
            "setObjectSamplerProperty": createSetObjectPropertyFromContextValue((ctx, id) => ctx.getSampler(id)),
            "setObjectRenderPassProperty": createSetObjectPropertyFromContextValue((ctx, id) => ctx.getRenderPass(id)),


            ////////////////////////////////
            // Release GPU resource
            "releaseBindGroupLayout": (ctxObjId: number, bindGroupLayoutId: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                ctx.releaseBindGroupLayout(bindGroupLayoutId);
            },
            "releaseBindGroup": (ctxObjId: number, bindGroupId: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                ctx.releaseBindGroup(bindGroupId);
            },
            "releaseShaderModule": (ctxObjId: number, shaderModuleId: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                ctx.releaseShaderModule(shaderModuleId);
            },
            "releasePipelineLayout": (ctxObjId: number, pipelineLayoutId: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                ctx.releasePipelineLayout(pipelineLayoutId);
            },
            "releasePipeline": (ctxObjId: number, pipelineId: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                ctx.releasePipeline(pipelineId);
            },
            "releaseBuffer": (ctxObjId: number, bufferId: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                ctx.releaseBuffer(bufferId);
            },
            "releaseTexture": (ctxObjId: number, textureId: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                ctx.releaseTexture(textureId);
            },
            "releaseTextureView": (ctxObjId: number, textureViewId: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                ctx.releaseTextureView(textureViewId);
            },
            "releaseSampler": (ctxObjId: number, samplerId: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                ctx.releaseSampler(samplerId);
            },
            "releaseRenderPass": (ctxObjId: number, renderPassId: number) => {
                const ctx = objLib.get(ctxObjId) as Context;
                ctx.releaseRenderPass(renderPassId);
            },
        },
    };
}
