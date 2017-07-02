import { ChartDrawerState } from '../types/ChartDrawerState';

export default class History {
    private snapshots: ChartDrawerState[] = [];
    private lastSnapshotIndex: number = 0;

    public constructor(state: ChartDrawerState) {
        this.snapshots.push(state);
    }

    public getLastState(): ChartDrawerState {
        return this.snapshots[this.lastSnapshotIndex];
    }

    public undo() {
        this.lastSnapshotIndex = Math.max(0, this.lastSnapshotIndex - 1);
    }

    public redo() {
        this.lastSnapshotIndex = Math.min(this.snapshots.length - 1, this.lastSnapshotIndex + 1);
    }

    public addNewSnapshot(state: ChartDrawerState) {
        this.snapshots = this.snapshots.slice(0, this.lastSnapshotIndex + 1);
        this.snapshots.push(state);
        ++this.lastSnapshotIndex;
    }
}