import * as React from 'react';
import {harmonicFunctionType} from '../constants/harmonicFunctionType';
import Harmonic from './Harmonic';

export interface HarmonicStringProps {
    harmonic: Harmonic;
    selected: boolean;
}

export default function HarmonicString(props: HarmonicStringProps) {

    let getHarmonicFunctionString = (type: harmonicFunctionType) => {
        if (type === harmonicFunctionType.Sin) {
            return 'sin';
        }
        if (type === harmonicFunctionType.Cos) {
            return 'cos';
        }
        throw new Error('Unknown harmonic function: ' + type);
    };

    let prependPlusIfPositive = (x: number): string => {
        return (x >= 0) ? ' + ' + x : ' ' + x;
    };

    let formatMultiplier = (x: number): string => {
        if (x === 1) {
            return '';
        }
        if (x === -1) {
            return '-';
        }
        return String(x);
    };

    let selected = props.selected ? 'selected' : '';
    let h = props.harmonic;
    let equationString = '%amplitude%%harmonic%(%frequency%x%phase%)';

    equationString = equationString.replace('%amplitude%', formatMultiplier(h.amplitude))
        .replace('%harmonic%', getHarmonicFunctionString(h.harmonicFunction))
        .replace('%frequency%', formatMultiplier(h.frequency))
        .replace('%phase%', prependPlusIfPositive(h.phase));

    return (
        <li className={selected}>{equationString}</li>
    );
}