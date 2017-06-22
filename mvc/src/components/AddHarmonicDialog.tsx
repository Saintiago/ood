import * as React from 'react';
import HarmonicDetailed from './HarmonicDetailed';
import Harmonic from './Harmonic';
import { Dialog, FlatButton } from 'material-ui';
import * as style from '../constants/styles';
import {getHarmonicString} from './HarmonicsList';

interface AddHarmonicDialogProps {
    visible: boolean;
    tmpHarmonic: Harmonic;
    onAddClicked: () => void;
    onCancelClicked: () => void;
    onHarmonicChange: (newHarmonic: Harmonic, index: number) => void;
}

export default function AddHarmonicDialog(props: AddHarmonicDialogProps) {

    const actions = [
        (
            <FlatButton label="Cancel" primary={false} onClick={props.onCancelClicked} />
        ),
        (
            <FlatButton label="Add" primary={true} keyboardFocused={true} onClick={props.onAddClicked} />
        )
    ];

    return  (
        <Dialog
            title="Add New harmonic function"
            actions={actions}
            modal={false}
            open={props.visible}
            contentStyle={style.addHarmonicDialog}
            onRequestClose={props.onCancelClicked}
        >
            <HarmonicDetailed
                name="add"
                harmonic={props.tmpHarmonic}
                onHarmonicChange={props.onHarmonicChange}
                index={-1}
            />
            <div style={style.addHarmonicDialogPreview}>
                {getHarmonicString(props.tmpHarmonic)}
            </div>
        </Dialog>
    );
}