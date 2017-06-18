import * as React from 'react';
import {harmonicFunctionType} from '../constants/harmonicFunctionType';
import Harmonic from './Harmonic';
import {getHarmonicFunctionString} from './HarmonicString';

export interface HarmonicDetailedProps {
    harmonic: Harmonic;
    name: string;
    readonly: boolean;
    onHarmonicChange?: (newHarmonic: Harmonic) => void;
}

interface RadioChoice {
    label: string;
    value: string;
    checked: boolean;
}

export default function HarmonicDetailed(props: HarmonicDetailedProps) {

    let radiosArray = [];
    let sin = getHarmonicFunctionString(harmonicFunctionType.Sin);
    let cos = getHarmonicFunctionString(harmonicFunctionType.Cos);
    radiosArray.push({label: sin, value: sin, checked: (harmonicFunctionType.Sin === props.harmonic.harmonicFunction)});
    radiosArray.push({label: cos, value: cos, checked: (harmonicFunctionType.Cos === props.harmonic.harmonicFunction)});

    let onHarmonicChange = (typeof props.onHarmonicChange !== 'undefined') ? props.onHarmonicChange : () => { return; };
    let localHarmonic = props.harmonic;
    let handleAmplitudeChange = (value: number) => {
        localHarmonic.amplitude = value;
        onHarmonicChange(localHarmonic);
    };

    let handleFrequencyChange = (value: number) => {
        localHarmonic.frequency = value;
        onHarmonicChange(localHarmonic);
    };

    let handlePhaseChange = (value: number) => {
        localHarmonic.phase = value;
        onHarmonicChange(localHarmonic);
    };

    let handleHFunctionChange = (e: React.FormEvent<HTMLInputElement>) => {
        localHarmonic.harmonicFunction = (e.currentTarget.value === 'Sin')
            ? harmonicFunctionType.Sin
            : harmonicFunctionType.Cos;
        onHarmonicChange(localHarmonic);
    };

    function LabelledProperty(
        { label, value, onChange }: {label: string; value: number; onChange: (value: number) => void;  }
        ) {
        return (
            <li>
                <label >{label}</label>
                <input
                    type="number"
                    defaultValue={value.toString()}
                    readOnly={props.readonly}
                    onChange={e => onChange(Number(e.currentTarget.value))}
                />
            </li>
        );
    }

    function RadioButtons(
        {radios, onChange}: { radios: RadioChoice[]; onChange: (e: React.FormEvent<HTMLInputElement>) => void; }
        ) {

        let renderRadio = (i: number) => {
            let radio = radios[i];
            return (
                <span key={i}>
                <input
                    name={props.name + 'RadioButtons'}
                    type="radio"
                    value={radio.value}
                    defaultChecked={radio.checked}
                    disabled={props.readonly}
                    onChange={e => onChange(e)}
                />
                <label>{radio.label}</label>
            </span>
            );
        };

        let radioChoices = [];
        for (let i = 0; i < radios.length; ++i) {
            radioChoices.push(renderRadio(i));
        }

        return (
            <li>
                {radioChoices}
            </li>
        );
    }

    return (
        <ul className="harmonic_detailed">
            <LabelledProperty label="amplitude" value={props.harmonic.amplitude} onChange={handleAmplitudeChange} />
            <RadioButtons radios={radiosArray} onChange={handleHFunctionChange} />
            <LabelledProperty label="frequency" value={props.harmonic.frequency} onChange={handleFrequencyChange} />
            <LabelledProperty label="phase" value={props.harmonic.phase} onChange={handlePhaseChange} />
        </ul>
    );
}