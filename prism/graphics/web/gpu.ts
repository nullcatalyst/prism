import { Memory } from "../../../base/wasm/memory/memory";
import { ObjectLibrary } from "../../../base/wasm/object/object";
import { RefMap } from "../../../base/wasm/memory/ref_map";

import "./webgpu.typings";

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

    constructor(canvas: HTMLCanvasElement, awaitList: Promise<any>[]) {
        const entry = navigator.gpu;
        if (!entry) {
            throw new Error('WebGPU is not supported on this browser');
        }
        if (canvas == null) {
            throw new Error('canvas not found');
        }

        awaitList.push((async () => {
            const adapter = await entry.requestAdapter();
            if (adapter == null) {
                throw new Error('failed to get WebGPU hardware adapter');
            }

            const devicePixelRatio = (window.devicePixelRatio || 1);
            const clientWidth = canvas.clientWidth;
            const clientHeight = canvas.clientHeight;
            canvas.style.width = `${clientWidth / devicePixelRatio}px`;
            canvas.style.height = `${clientHeight / devicePixelRatio}px`;

            const device = await adapter.requestDevice();
            const context = canvas.getContext('webgpu');
            if (context == null) {
                throw new Error('failed to get WebGPU canvas context');
            }
            context.configure({
                "device": device,
                // TODO: At this time, it appears that chrome does not support sRGB, even though the spec says it's required to
                // format: 'bgra8unorm-srgb',
                "format": 'bgra8unorm',
                "alphaMode": 'opaque',
            });

            this._device = device;
            this._context = context;
        })());
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

    createBuffer(usage: GPUBufferUsageFlags, fullSize: number, offset: number, data: ArrayBuffer) {
        const copy = data.byteLength > 0;
        const buffer = this._device.createBuffer({
            "usage": usage,
            "size": fullSize,
            "mappedAtCreation": copy,
        });
        if (copy) {
            const writeArray = new Uint8Array(buffer.getMappedRange());
            writeArray.set(new Uint8Array(data), offset);
            buffer.unmap();
        }
        return this._buffers.create(buffer);
    }

    updateBuffer(bufferId: number, offset: number, data: ArrayBuffer) {
        this._device.queue.writeBuffer(this._buffers.get(bufferId), offset, data);
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

    createSamplerComparison(addressMode: GPUAddressMode, minFilter: GPUFilterMode, magFilter: GPUFilterMode, mipmapFilter: GPUFilterMode, compare: GPUCompareFunction) {
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
    beginRenderPass(desc: GPURenderPassDescriptor, width: number, height: number) {
        const passEncoder = this._drawEncoder.beginRenderPass(desc);
        passEncoder.setViewport(0, 0, width, height, 0, 1);
        passEncoder.setScissorRect(0, 0, width, height);
        return this._renderPasses.create(passEncoder);
    }
    endRenderPass(renderPassId: number) { this._renderPasses.get(renderPassId).end(); }
    setPipeline(renderPassId: number, pipelineId: number) { this._renderPasses.get(renderPassId).setPipeline(this._pipelines.get(pipelineId)); }
    setBindGroup(renderPassId: number, slot: number, bindGroupId: number) { this._renderPasses.get(renderPassId).setBindGroup(slot, this._bindGroups.get(bindGroupId)); }
    setBuffer(renderPassId: number, slot: number, bufferId: number, offset: number) { this._renderPasses.get(renderPassId).setVertexBuffer(slot, this._buffers.get(bufferId), offset); }
    setIndexU16Buffer(renderPassId: number, bufferId: number, offset: number, size: number) { this._renderPasses.get(renderPassId).setIndexBuffer(this._buffers.get(bufferId), 'uint16', offset, size >= 0 ? size : undefined); }
    setIndexU32Buffer(renderPassId: number, bufferId: number, offset: number, size: number) { this._renderPasses.get(renderPassId).setIndexBuffer(this._buffers.get(bufferId), 'uint32', offset, size >= 0 ? size : undefined); }
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

export function createGpuWasmImport(memory: Memory, objLib: ObjectLibrary, awaitList: Promise<any>[]) {
    function _createSetObjectPropertyFromContextValue(getter: (ctx: Context, value: number) => any) {
        return objLib.wrapFuncWithObjectParam(
            (ctx: Context, objId: number, namePtr: number, valueId: number) => {
                const value = getter(ctx, valueId);
                if (namePtr === 0) {
                    // If the name is null, then the object must be an array that we are pushing onto
                    objLib.arrayPushRaw(objId, value);
                } else {
                    objLib.setRawProperty(objId, memory.createJsString(namePtr), value);
                }
            },
            0);
    }

    return {
        "gpu": {
            "getPixelRatio": () => window.devicePixelRatio,

            "createContext": objLib.wrapFuncWithObjectParam(
                (canvas: HTMLCanvasElement) => objLib.create(new Context(canvas, awaitList)),
                0),
            "createBindGroupLayout": objLib.wrapFuncWithObjectParam(
                objLib.wrapFuncWithObjectParam(
                    (ctx: Context, desc: GPUBindGroupLayoutDescriptor) => ctx.createBindGroupLayout(desc),
                    0),
                1),
            "createBindGroup": objLib.wrapFuncWithObjectParam(
                objLib.wrapFuncWithObjectParam(
                    (ctx: Context, desc: GPUBindGroupDescriptor) => ctx.createBindGroup(desc),
                    0),
                1),
            "createShaderModule": memory.wrapFuncWithStringParam(
                objLib.wrapFuncWithObjectParam(
                    (ctx: Context, sourceUrl: string) => ctx.createShaderModule(sourceUrl),
                    0),
                1),
            "createPipelineLayout": objLib.wrapFuncWithObjectParam(
                objLib.wrapFuncWithObjectParam(
                    (ctx: Context, desc: GPUPipelineLayoutDescriptor) => ctx.createPipelineLayout(desc),
                    0),
                1),
            "createRenderPipeline": objLib.wrapFuncWithObjectParam(
                objLib.wrapFuncWithObjectParam(
                    (ctx: Context, desc: GPURenderPipelineDescriptor) => ctx.createRenderPipeline(desc),
                    0),
                1),
            "createBuffer": memory.wrapFuncWithBufferParam(
                objLib.wrapFuncWithObjectParam(
                    (ctx: Context, usage: number, fullSize: number, offset: number, data: ArrayBuffer) => ctx.createBuffer(usage, fullSize, offset, data),
                    0),
                4),
            "updateBuffer": memory.wrapFuncWithBufferParam(
                objLib.wrapFuncWithObjectParam(
                    (ctx: Context, bufferId: number, offset: number, data: ArrayBuffer) => ctx.updateBuffer(bufferId, offset, data),
                    0),
                3),
            "createTexture2d": memory.wrapFuncWithStringParam(
                objLib.wrapFuncWithObjectParam(
                    (ctx: Context, usage: number, format: GPUTextureFormat, width: number, height: number) => ctx.createTexture2d(usage, format, width, height),
                    0),
                2),
            "updateTexture2d": memory.wrapFuncWithBufferParam(
                objLib.wrapFuncWithObjectParam(
                    (ctx: Context, textureId: number, width: number, height: number, data: ArrayBuffer) => ctx.updateTexture2d(textureId, width, height, data),
                    0),
                4),
            "createTextureView2d": memory.wrapFuncWithStringParam(
                objLib.wrapFuncWithObjectParam(
                    (ctx: Context, textureId: number, format: GPUTextureFormat) => ctx.createTextureView2d(textureId, format),
                    0),
                2),
            "createSampler": memory.wrapFuncWithStringParam(
                memory.wrapFuncWithStringParam(
                    memory.wrapFuncWithStringParam(
                        memory.wrapFuncWithStringParam(
                            objLib.wrapFuncWithObjectParam(
                                (ctx: Context, addressMode: GPUAddressMode, minFilter: GPUFilterMode, magFilter: GPUFilterMode, mipmapFilter: GPUFilterMode) => ctx.createSampler(addressMode, minFilter, magFilter, mipmapFilter),
                                0),
                            1),
                        2),
                    3),
                4),
            "createSamplerComparison": memory.wrapFuncWithStringParam(
                memory.wrapFuncWithStringParam(
                    memory.wrapFuncWithStringParam(
                        memory.wrapFuncWithStringParam(
                            memory.wrapFuncWithStringParam(
                                objLib.wrapFuncWithObjectParam(
                                    (ctx: Context, addressMode: GPUAddressMode, minFilter: GPUFilterMode, magFilter: GPUFilterMode, mipmapFilter: GPUFilterMode, compare: GPUCompareFunction) => ctx.createSamplerComparison(addressMode, minFilter, magFilter, mipmapFilter, compare),
                                    0),
                                1),
                            2),
                        3),
                    4),
                5),


            ////////////////////////////////
            // Render pass
            "beginRenderPass": objLib.wrapFuncWithObjectParam(
                objLib.wrapFuncWithObjectParam(
                    (ctx: Context, desc: GPURenderPassDescriptor, width: number, height: number) => ctx.beginRenderPass(desc, width, height),
                    0),
                1),
            "endRenderPass": objLib.wrapFuncWithObjectParam(
                (ctx: Context, renderPassId: number) => ctx.endRenderPass(renderPassId),
                0),
            "setPipeline": objLib.wrapFuncWithObjectParam(
                (ctx: Context, renderPassId: number, pipelineId: number) => ctx.setPipeline(renderPassId, pipelineId),
                0),
            "setBindGroup": objLib.wrapFuncWithObjectParam(
                (ctx: Context, renderPassId: number, slot: number, bindGroupId: number) => ctx.setBindGroup(renderPassId, slot, bindGroupId),
                0),
            "setBuffer": objLib.wrapFuncWithObjectParam(
                (ctx: Context, renderPassId: number, slot: number, bufferId: number, offset: number) => ctx.setBuffer(renderPassId, slot, bufferId, offset),
                0),
            "setIndexU16Buffer": objLib.wrapFuncWithObjectParam(
                (ctx: Context, renderPassId: number, bufferId: number, offset: number, size: number) => ctx.setIndexU16Buffer(renderPassId, bufferId, offset, size),
                0),
            "setIndexU32Buffer": objLib.wrapFuncWithObjectParam(
                (ctx: Context, renderPassId: number, bufferId: number, offset: number, size: number) => ctx.setIndexU16Buffer(renderPassId, bufferId, offset, size),
                0),
            "draw": objLib.wrapFuncWithObjectParam(
                (ctx: Context, renderPassId: number, vertexCount: number, instanceCount: number, firstVertex: number, firstInstance: number) => ctx.draw(renderPassId, vertexCount, instanceCount, firstVertex, firstInstance),
                0),
            "drawIndexed": objLib.wrapFuncWithObjectParam(
                (ctx: Context, renderPassId: number, vertexCount: number, instanceCount: number, firstIndex: number, baseVertex: number, firstInstance: number) => ctx.drawIndexed(renderPassId, vertexCount, instanceCount, firstIndex, baseVertex, firstInstance),
                0),
            "drawIndirect": objLib.wrapFuncWithObjectParam(
                (ctx: Context, renderPassId: number, bufferId: number, indirectOffset: number) => ctx.drawIndirect(renderPassId, bufferId, indirectOffset),
                0),
            "drawIndexedIndirect": objLib.wrapFuncWithObjectParam(
                (ctx: Context, renderPassId: number, bufferId: number, indirectOffset: number) => ctx.drawIndexedIndirect(renderPassId, bufferId, indirectOffset),
                0),

            "getSwapChainView": objLib.wrapFuncWithObjectParam(
                (ctx: Context) => ctx.getSwapChainView(),
                0),
            "startFrame": objLib.wrapFuncWithObjectParam(
                (ctx: Context) => ctx.startFrame(),
                0),
            "presentFrame": objLib.wrapFuncWithObjectParam(
                (ctx: Context) => ctx.presentFrame(),
                0),


            ////////////////////////////////
            // Set object property to GPU resource
            "setObjectBindGroupLayoutProperty": _createSetObjectPropertyFromContextValue((ctx, id) => ctx.getBindGroupLayout(id)),
            "setObjectBindGroupProperty": _createSetObjectPropertyFromContextValue((ctx, id) => ctx.getBindGroup(id)),
            "setObjectShaderModuleProperty": _createSetObjectPropertyFromContextValue((ctx, id) => ctx.getShaderModule(id)),
            "setObjectPipelineLayoutProperty": _createSetObjectPropertyFromContextValue((ctx, id) => ctx.getPipelineLayout(id)),
            "setObjectPipelineProperty": _createSetObjectPropertyFromContextValue((ctx, id) => ctx.getPipeline(id)),
            "setObjectBufferProperty": _createSetObjectPropertyFromContextValue((ctx, id) => ctx.getBuffer(id)),
            "setObjectTextureProperty": _createSetObjectPropertyFromContextValue((ctx, id) => ctx.getTexture(id)),
            "setObjectTextureViewProperty": _createSetObjectPropertyFromContextValue((ctx, id) => ctx.getTextureView(id)),
            "setObjectSamplerProperty": _createSetObjectPropertyFromContextValue((ctx, id) => ctx.getSampler(id)),
            "setObjectRenderPassProperty": _createSetObjectPropertyFromContextValue((ctx, id) => ctx.getRenderPass(id)),


            ////////////////////////////////
            // Release GPU resource
            "releaseBindGroupLayout": objLib.wrapFuncWithObjectParam(
                (ctx: Context, bindGroupLayoutId: number) => ctx.releaseBindGroupLayout(bindGroupLayoutId),
                0),
            "releaseBindGroup": objLib.wrapFuncWithObjectParam(
                (ctx: Context, bindGroupId: number) => ctx.releaseBindGroup(bindGroupId),
                0),
            "releaseShaderModule": objLib.wrapFuncWithObjectParam(
                (ctx: Context, shaderModuleId: number) => ctx.releaseShaderModule(shaderModuleId),
                0),
            "releasePipelineLayout": objLib.wrapFuncWithObjectParam(
                (ctx: Context, pipelineLayoutId: number) => ctx.releasePipelineLayout(pipelineLayoutId),
                0),
            "releasePipeline": objLib.wrapFuncWithObjectParam(
                (ctx: Context, pipelineId: number) => ctx.releasePipeline(pipelineId),
                0),
            "releaseBuffer": objLib.wrapFuncWithObjectParam(
                (ctx: Context, bufferId: number) => ctx.releaseBuffer(bufferId),
                0),
            "releaseTexture": objLib.wrapFuncWithObjectParam(
                (ctx: Context, textureId: number) => ctx.releaseTexture(textureId),
                0),
            "releaseTextureView": objLib.wrapFuncWithObjectParam(
                (ctx: Context, textureViewId: number) => ctx.releaseTextureView(textureViewId),
                0),
            "releaseSampler": objLib.wrapFuncWithObjectParam(
                (ctx: Context, samplerId: number) => ctx.releaseSampler(samplerId),
                0),
            "releaseRenderPass": objLib.wrapFuncWithObjectParam(
                (ctx: Context, renderPassId: number) => ctx.releaseRenderPass(renderPassId),
                0),
        },
    };
}
