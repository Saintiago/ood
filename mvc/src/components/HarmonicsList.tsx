import * as React from 'react';
import HarmonicString from './HarmonicString';
import Harmonic from './Harmonic';

interface HarmonicsListProps {
    harmonics: Harmonic[];
    selected: number
}

export default function HarmonicsList(props: HarmonicsListProps) {

    let renderHarmonic = function(i: number) {
        let isSelected = (i === props.selected);
        return (
            <HarmonicString key={i} harmonic={props.harmonics[i]} selected={isSelected} />
        );
    };

    let renderHarmonicsList = function() {
        let rows = [];
        for (let i = 0; i < props.harmonics.length; ++i) {
            rows.push(renderHarmonic(i));
        }
        return (
            <ul className="harmonic_list">
                {rows}
            </ul>
        );
    };

    return (
        <div className="harmonic_list_wrapper">
            {renderHarmonicsList()}
        </div>
    );
}