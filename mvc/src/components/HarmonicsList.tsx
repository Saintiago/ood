import * as React from 'react';
import Harmonic from './Harmonic';
import {harmonicFunctionType} from '../constants/harmonicFunctionType';
import {List, ListItem, makeSelectable} from 'material-ui';
import * as style from '../constants/styles';

interface HarmonicsListProps {
    harmonics: Harmonic[];
    selected: number;
    onSelectHarmonic: (index: number) => void;
}

export default function HarmonicsList({harmonics, selected, onSelectHarmonic}: HarmonicsListProps) {

    let renderHarmonic = function(i: number) {
        return (
            <ListItem
                key={i}
                value={i}
                primaryText={getHarmonicString(harmonics[i])}
                onClick={() => onSelectHarmonic(i)}
            />
        );
    };

    let renderHarmonicsList = function() {
        let rows = [];
        for (let i = 0; i < harmonics.length; ++i) {
            rows.push(renderHarmonic(i));
        }
        return rows;
    };

    let SelectableList = makeSelectable(List);

    return (
        <SelectableList style={style.harmonicListInner} value={selected}>
            {renderHarmonicsList()}
        </SelectableList>
    );
}

export function getHarmonicFunctionString(type: harmonicFunctionType) {
    if (type === harmonicFunctionType.Sin) {
        return 'sin';
    }
    if (type === harmonicFunctionType.Cos) {
        return 'cos';
    }
    throw new Error('Unknown harmonic function: ' + type);
}

function getHarmonicString(harmonic: Harmonic) {

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

    let h = harmonic;
    let equationString = '%amplitude%%harmonic%(%frequency%x%phase%)';

    equationString = equationString.replace('%amplitude%', formatMultiplier(h.amplitude))
        .replace('%harmonic%', getHarmonicFunctionString(h.harmonicFunction))
        .replace('%frequency%', formatMultiplier(h.frequency))
        .replace('%phase%', prependPlusIfPositive(h.phase));

    return equationString;
}