import * as React from 'react';
import Harmonic from './Harmonic';
import {harmonicFunctionType} from '../constants/harmonicFunctionType';

function HarmonicString(props: any) {

    let getHarmonicFunctionString = function (type: harmonicFunctionType) {
        if (type === harmonicFunctionType.Sin) {
            return 'sin';
        }
        if (type === harmonicFunctionType.Cos) {
            return 'cos';
        }
        throw new Error('Unknown harmonic function: ' + type);
    };

    let prependPlusIfPositive = function (x: number): string {
        return (x >= 0) ? ' + ' + x : ' ' + x;
    };

    let formatMultiplier = function(x: number): string {
        if (x === 1) {
            return '';
        }
        if (x === -1) {
            return '-';
        }
        return String(x);
    };

    let h = props.harmonic;
    let equationString = '%amplitude%%harmonic%(%frequency%x%phase%)';
    equationString = equationString.replace('%amplitude%', formatMultiplier(h.amplitude))
                                   .replace('%harmonic%', getHarmonicFunctionString(h.harmonicFunction))
                                   .replace('%frequency%', formatMultiplier(h.frequency))
                                   .replace('%phase%', prependPlusIfPositive(h.phase));

    return (
        <li>{equationString}</li>
    );
}

export default class HarmonicsList extends React.Component<any, any> {
    constructor() {
        super();

        let harmonicsList = [] as Harmonic[];

        harmonicsList.push(new Harmonic(4.5, 23, -1, harmonicFunctionType.Sin));
        harmonicsList.push(new Harmonic(-11, 4, 1, harmonicFunctionType.Cos));
        harmonicsList.push(new Harmonic(1, 1, 3, harmonicFunctionType.Sin));

        this.state = {
            harmonics: harmonicsList
        };
    }

    renderHarmonic(i: number) {
        return (
            <HarmonicString key={i} harmonic={this.state.harmonics[i]} />
        );
    }

    renderHarmonicsList() {
        let rows = [];
        for (let i = 0; i < this.state.harmonics.length; ++i) {
            rows.push(this.renderHarmonic(i));
        }
        return (
                <ul className="harmonic_list">
                    {rows}
                </ul>
        );
    }

    render() {
        return (
            <div className="harmonic_list_wrapper">
                {this.renderHarmonicsList()}
            </div>
        );
    }
}