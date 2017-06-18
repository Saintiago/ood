import * as React from 'react';
import HarmonicDetailed from './HarmonicDetailed';
import Harmonic from './Harmonic';

interface AddHarmonicDialogProps {
    visible: boolean;
    tmpHarmonic: Harmonic;
    onAddClicked: () => void;
    onCancelClicked: () => void;
    onHarmonicChange: (newHarmonic: Harmonic) => void;
}

export default function AddHarmonicDialog(props: AddHarmonicDialogProps) {
    let addHarmonicDialogStyle = {
        display: (props.visible) ? 'initial' : 'none'
    };
    return  (
        <div className="add_harmonic_dialog" style={addHarmonicDialogStyle}>
            <HarmonicDetailed
                name="add"
                readonly={false}
                harmonic={props.tmpHarmonic}
                onHarmonicChange={props.onHarmonicChange}
            />
            <button onClick={props.onAddClicked}>Add</button>
            <button onClick={props.onCancelClicked}>Cancel</button>
        </div>
    );
}