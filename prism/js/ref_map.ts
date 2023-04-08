export class RefMap<T> {
    private _next_id = 0;
    private readonly _map = new Map<number, T>;

    get(id: number): T {
        return this._map.get(id)!;
    }

    create(value: T): number {
        if (this._next_id > 0xffffffff) {
            throw new Error('id is larger than the max value of a 32bit integer, new reference cannot be created');
        }
        ++this._next_id;
        this._map.set(this._next_id, value);
        return this._next_id;
    }

    release(id: number): void {
        this._map.delete(id);
    }
}
