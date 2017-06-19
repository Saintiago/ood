import * as React from 'react';
import HarmonicDetailed from './HarmonicDetailed';
import Harmonic from './Harmonic';
import { Dialog, FlatButton } from 'material-ui';

interface AddHarmonicDialogProps {
    visible: boolean;
    tmpHarmonic: Harmonic;
    onAddClicked: () => void;
    onCancelClicked: () => void;
    onHarmonicChange: (newHarmonic: Harmonic) => void;
}

export default function AddHarmonicDialog(props: AddHarmonicDialogProps) {

    const actions = [
        <FlatButton
            label="Cancel"
            primary={false}
            onClick={props.onCancelClicked}
        />,
        <FlatButton
            label="Add"
            primary={true}
            keyboardFocused={true}
            onClick={props.onAddClicked}
        />,
    ];

    const customContentStyle = {
        width: 400
    };

    return  (
        <Dialog
            title="Add New harmonic function"
            actions={actions}
            modal={false}
            open={props.visible}
            contentStyle={customContentStyle}
            onRequestClose={props.onCancelClicked}
        >
            <HarmonicDetailed
                name="add"
                readonly={false}
                harmonic={props.tmpHarmonic}
                onHarmonicChange={props.onHarmonicChange}
            />
        </Dialog>
    );
}