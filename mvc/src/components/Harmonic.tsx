import {harmonicFunctionType} from '../constants/harmonicFunctionType';

export default class Harmonic {
    constructor(public amplitude: number,
                public frequency: number,
                public phase: number,
                public harmonicFunction: harmonicFunctionType) {
    }

    public getData(xValues: number[]) {
        let data: {x: number, y: number}[] = [];
        for (let x of xValues) {
            let y = this.getY(x);
            data.push({x, y});
        }
        return data;
    }

    getY = (x: number): number => {
        return this.amplitude * this.getHarmonicFunction(this.frequency * x + this.phase);
    }

    private getHarmonicFunction(arg: number) {
        switch (this.harmonicFunction) {
            case harmonicFunctionType.Sin: {
                return Math.sin(arg);
            }
            case harmonicFunctionType.Cos: {
                return Math.cos(arg);
            }
            default: {
                throw Error('Unknown harmonic function');
            }
        }
    }
}