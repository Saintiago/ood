import * as React from 'react';
// import {harmonicFunctionType} from '../constants/harmonicFunctionType';
import Harmonic from './Harmonic';

export interface HarmonicDetailedProps {
    harmonic: Harmonic;
}

export default function HarmonicDetailed(props: HarmonicDetailedProps) {

    return (
        <ul className="harmonic_detailed">
            <LabelledProperty id="harmonicDetailedAmplitude" label="amplitude" value={props.harmonic.amplitude}/>
            <LabelledProperty id="harmonicDetailedFrequency" label="frequency" value={props.harmonic.frequency}/>
            <LabelledProperty id="harmonicDetailedPhase" label="phase" value={props.harmonic.phase}/>
            <LabelledProperty
                id="harmonicDetailedHarmonicFunction"
                label="harmonicFunction"
                value={props.harmonic.harmonicFunction}
            />
        </ul>
    );
}

function LabelledProperty(props: {id: string; label: string; value: number; }) {
    return (
        <li>
            <label htmlFor={props.id}>{props.label}</label>
            <input type="text" id={props.id} value={props.value} />
        </li>
    );
}