import * as React from 'react';
import {harmonicFunctionType} from '../constants/harmonicFunctionType';
import Harmonic from './Harmonic';
import {getHarmonicFunctionString} from './HarmonicString';

export interface HarmonicDetailedProps {
    harmonic: Harmonic;
}

interface RadioChoice {
    label: string;
    value: string;
    checked: boolean;
}

export default function HarmonicDetailed(props: HarmonicDetailedProps) {

    let radios = [];
    let sin = getHarmonicFunctionString(harmonicFunctionType.Sin);
    let cos = getHarmonicFunctionString(harmonicFunctionType.Cos);
    radios.push({label: sin, value: sin, checked: (harmonicFunctionType.Sin === props.harmonic.harmonicFunction)});
    radios.push({label: cos, value: cos, checked: (harmonicFunctionType.Cos === props.harmonic.harmonicFunction)});

    return (
        <ul className="harmonic_detailed">
            <LabelledProperty id="harmonicDetailedAmplitude" label="amplitude" value={props.harmonic.amplitude} />
            <RadioButtons name="harmonic_detailed_harmonic_function" radios={radios} />
            <LabelledProperty id="harmonicDetailedFrequency" label="frequency" value={props.harmonic.frequency} />
            <LabelledProperty id="harmonicDetailedPhase" label="phase" value={props.harmonic.phase} />
        </ul>
    );
}

function LabelledProperty(props: {id: string; label: string; value: number; }) {
    return (
        <li>
            <label htmlFor={props.id}>{props.label}</label>
            <input type="text" id={props.id} value={props.value} readOnly={true} />
        </li>
    );
}

function RadioButtons(props: { name: string; radios: RadioChoice[] }) {

    let renderRadio = (radio: RadioChoice) => {
        return (
            <span>
                <input type="radio" name={props.name} value={radio.value} checked={radio.checked} readOnly={true} />
                <label>{radio.label}</label>
            </span>
        );
    };

    let radioChoices = [];
    for (let radio of props.radios) {
        radioChoices.push(renderRadio(radio));
    }

    return (
        <li>
            {radioChoices}
        </li>
    );
}