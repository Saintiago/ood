//import * as React from 'react';

import {harmonicFunctionType} from '../constants/harmonicFunctionType';

export default class Harmonic {
    constructor(public amplitude: number,
                public frequency: number,
                public phase: number,
                public harmonicFunction: harmonicFunctionType) {
    }

    public getY(x: number) {
        return this.amplitude * this.getHarmonicFunction(this.frequency * x + this.phase);
    }

    private getHarmonicFunction(arg: number){
        switch (this.harmonicFunction)
        {
            case harmonicFunctionType.Sin: {
                return Math.sin(arg);
            }
            case harmonicFunctionType.Cos: {
                return Math.cos(arg);
            }
        }
    }
}