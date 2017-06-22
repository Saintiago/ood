import * as React from 'react';
import {harmonicFunctionType} from '../constants/harmonicFunctionType';
import Harmonic from './Harmonic';
import {getHarmonicFunctionString} from './HarmonicsList';
import {TextField, RadioButton, RadioButtonGroup} from 'material-ui';
import * as style from '../constants/styles';

export interface HarmonicDetailedProps {
    harmonic: Harmonic;
    index: number;
    name: string;
    onHarmonicChange: (newHarmonic: Harmonic, index: number) => void;
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

    let localHarmonic = new Harmonic(
        props.harmonic.amplitude,
        props.harmonic.frequency,
        props.harmonic.phase,
        props.harmonic.harmonicFunction
    );

    let handleAmplitudeChange = (value: number) => {
        if (!isNaN(value)) {
            localHarmonic.amplitude = value;
            props.onHarmonicChange(localHarmonic, props.index);
        }
    };

    let handleFrequencyChange = (value: number) => {
        if (!isNaN(value)) {
            localHarmonic.frequency = value;
            props.onHarmonicChange(localHarmonic, props.index);
        }
    };

    let handlePhaseChange = (value: number) => {
        if (!isNaN(value)) {
            localHarmonic.phase = value;
            props.onHarmonicChange(localHarmonic, props.index);
        }
    };

    let handleHFunctionChange = (value: string) => {
        localHarmonic.harmonicFunction = (value === 'sin')
            ? harmonicFunctionType.Sin
            : harmonicFunctionType.Cos;
        props.onHarmonicChange(localHarmonic, props.index);
    };

    function LabelledProperty(
        { label, value, onChange }: {label: string; value: number; onChange: (value: number) => void;  }
        ) {
        return (
            <TextField
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
                key={i}
                value={radio.value}
                label={radio.label}
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
        <div style={style.harmonicDetailed}>
            <LabelledProperty label="amplitude" value={props.harmonic.amplitude} onChange={handleAmplitudeChange} />
            <RadioButtons radios={radiosArray} onChange={handleHFunctionChange} />
            <LabelledProperty label="frequency" value={props.harmonic.frequency} onChange={handleFrequencyChange} />
            <LabelledProperty label="phase" value={props.harmonic.phase} onChange={handlePhaseChange} />
        </div>
    );
}