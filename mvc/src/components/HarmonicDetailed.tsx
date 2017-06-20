import * as React from 'react';
import {harmonicFunctionType} from '../constants/harmonicFunctionType';
import Harmonic from './Harmonic';
import {getHarmonicFunctionString} from './HarmonicsList';
import {TextField, RadioButton, RadioButtonGroup} from 'material-ui';
import * as style from '../constants/styles';

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

    let handleHFunctionChange = (value: string) => {
        localHarmonic.harmonicFunction = (value === 'Sin')
            ? harmonicFunctionType.Sin
            : harmonicFunctionType.Cos;
        onHarmonicChange(localHarmonic);
    };

    function LabelledProperty(
        { label, value, onChange }: {label: string; value: number; onChange: (value: number) => void;  }
        ) {
        return (
            <TextField
                readOnly={props.readonly}
                hintText={label}
                defaultValue={value.toString()}
                floatingLabelText={label}
                onChange={(e: React.FormEvent<HTMLInputElement>, newValue: string) => onChange(Number(newValue))}
            />
        );
    }

    function RadioButtons(
        {radios, onChange}: { radios: RadioChoice[]; onChange: (newValue: string) => void; }
        ) {

        let renderRadio = (i: number) => {
            let radio = radios[i];
            return (
            <RadioButton
                value={radio.value}
                label={radio.label}
                disabled={props.readonly}
            />
            );
        };

        let radioChoices = [];
        for (let i = 0; i < radios.length; ++i) {
            radioChoices.push(renderRadio(i));
        }

        return (
            <RadioButtonGroup
                name={props.name + 'RadioButtons'}
                valueSelected={getHarmonicFunctionString(props.harmonic.harmonicFunction)}
                onChange={(e: React.FormEvent<HTMLInputElement>, newValue: string) => onChange(newValue)}
            >
                {radioChoices}
            </RadioButtonGroup>
        );
    }

    return (
        <div style={style.harmonic_detailed}>
            <LabelledProperty label="amplitude" value={props.harmonic.amplitude} onChange={handleAmplitudeChange} />
            <RadioButtons radios={radiosArray} onChange={handleHFunctionChange} />
            <LabelledProperty label="frequency" value={props.harmonic.frequency} onChange={handleFrequencyChange} />
            <LabelledProperty label="phase" value={props.harmonic.phase} onChange={handlePhaseChange} />
        </div>
    );
}