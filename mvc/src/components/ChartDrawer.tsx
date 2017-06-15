import * as React from 'react';
import Harmonic from './Harmonic';
import HarmonicsList from './HarmonicsList';
import HarmonicsDetailed from './HarmonicDetailed';
import {harmonicFunctionType} from '../constants/harmonicFunctionType';

interface HarmonicListState {
    harmonics: Harmonic[];
    selectedHarmonicIndex?: number;
}

export default class ChartDrawer extends React.Component<{}, HarmonicListState> {
    constructor() {
        super();

        let harmonicsList = [] as Harmonic[];

        harmonicsList.push(new Harmonic(4.5, 23, -1, harmonicFunctionType.Sin));
        harmonicsList.push(new Harmonic(-11, 4, 1, harmonicFunctionType.Cos));
        harmonicsList.push(new Harmonic(1, 1, 3, harmonicFunctionType.Sin));

        this.state = {
            harmonics: harmonicsList,
            selectedHarmonicIndex: 0
        };
    }

    render() {
        const { harmonics, selectedHarmonicIndex = 0 } = this.state;
        let selectedHarmonic = harmonics[selectedHarmonicIndex];
        return (
            <div className="harmonics_list_wrapper">
                <HarmonicsList harmonics={harmonics} selected={selectedHarmonicIndex} />
                <HarmonicsDetailed harmonic={selectedHarmonic} />
            </div>
        );
    }
}