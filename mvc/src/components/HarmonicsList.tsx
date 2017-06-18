import * as React from 'react';
import HarmonicString from './HarmonicString';
import Harmonic from './Harmonic';

interface HarmonicsListProps {
    harmonics: Harmonic[];
    selected: number;
    onSelectHarmonic: (index: number) => void;
}

export default function HarmonicsList({harmonics, selected, onSelectHarmonic}: HarmonicsListProps) {

    let renderHarmonic = function(i: number) {
        let isSelected = (i === selected);
        return (
            <HarmonicString
                onSelectHarmonic={onSelectHarmonic}
                index={i}
                key={i}
                harmonic={harmonics[i]}
                selected={isSelected}
            />
        );
    };

    let renderHarmonicsList = function() {
        let rows = [];
        for (let i = 0; i < harmonics.length; ++i) {
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