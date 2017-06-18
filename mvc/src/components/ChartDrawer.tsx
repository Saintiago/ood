import * as React from 'react';
import Harmonic from './Harmonic';
import HarmonicsList from './HarmonicsList';
import HarmonicsDetailed from './HarmonicDetailed';
import AddHarmonicDialog from './AddHarmonicDialog';
import HarmonicLineChart from './HarmonicLineChart';
import HarmonicTableChart from './HarmonicTableChart';
import {RaisedButton} from 'material-ui';

interface ChardDrawerProps {
    harmonics: Harmonic[];
    tmpHarmonic: Harmonic;
    selected: number;
    addDialogVisible: boolean;
    onSelectHarmonic: (index: number) => void;
    onAddDialogClicked: () => void;
    onDeleteClicked: (index: number) => void;
    onAddClicked: () => void;
    onCancelClicked: () => void;
    onAddHarmonicChange: (newHarmonic: Harmonic) => void;
}

export default function ChartDrawer (props: ChardDrawerProps )  {

    if (props.harmonics.length === 0) {
        return (
            <div className="harmonics_list_wrapper">
                <button onClick={props.onAddDialogClicked}>Add New</button>
                <AddHarmonicDialog
                    onAddClicked={props.onAddClicked}
                    onCancelClicked={props.onCancelClicked}
                    visible={props.addDialogVisible}
                    tmpHarmonic={props.tmpHarmonic}
                    onHarmonicChange={props.onAddHarmonicChange}
                />
            </div>
        );
    }

    let selectedHarmonic = props.harmonics[props.selected];
    let chartData = selectedHarmonic.getData([0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5]);
    return (
        <div className="harmonics_list_wrapper">
            <HarmonicsList
                onSelectHarmonic={props.onSelectHarmonic}
                harmonics={props.harmonics}
                selected={props.selected}
            />
            <RaisedButton onClick={props.onAddDialogClicked} label="Add New" />
            <RaisedButton onClick={() => {props.onDeleteClicked(props.selected); }} label="Delete Selected" />
            <AddHarmonicDialog
                onAddClicked={props.onAddClicked}
                onCancelClicked={props.onCancelClicked}
                visible={props.addDialogVisible}
                tmpHarmonic={props.tmpHarmonic}
                onHarmonicChange={props.onAddHarmonicChange}
            />
            <HarmonicsDetailed name="show" readonly={true} harmonic={selectedHarmonic} />
            <HarmonicLineChart data={chartData} />
            <HarmonicTableChart data={chartData} />
        </div>
    );
}