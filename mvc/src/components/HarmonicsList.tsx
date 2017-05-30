import * as React from 'react';
import Harmonic from './Harmonic';
import {harmonicFunctionType} from '../constants/harmonicFunctionType';

function HarmonicString(props: any) {
    let h = props.harmonic;
    return (
        <li>
            {h.amplitude} * {getHarmonicFunctionString(h.harmonicFunction)}({h.frequency}x{prependPlusIfPositive(h.phase)})
        </li>
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
        }
    }

    renderHarmonic(i: number) {
        return (
            <HarmonicString harmonic={this.state.harmonics[i]} />
        );
    }

    renderHarmonicsList(){
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

function getHarmonicFunctionString(type: harmonicFunctionType)
{
    if (type === harmonicFunctionType.Sin)
    {
        return "sin";
    }
    else if (type === harmonicFunctionType.Cos)
    {
        return "cos";
    }
    else
    {
        throw new Error('Unknown harmonic function: ' + type);
    }
}

function prependPlusIfPositive(x: number): string
{
    return (x >= 0) ? " + " + x : " " + x;
}