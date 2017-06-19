import * as React from 'react';
import Harmonic from './Harmonic';
import HarmonicsList from './HarmonicsList';
import HarmonicsDetailed from './HarmonicDetailed';
import AddHarmonicDialog from './AddHarmonicDialog';
import HarmonicLineChart from './HarmonicLineChart';
import HarmonicTableChart from './HarmonicTableChart';
import {RaisedButton, AppBar, Paper, Divider, Tabs, Tab } from 'material-ui';

interface ChardDrawerProps {
    harmonics: Harmonic[];
    tmpHarmonic: Harmonic;
    selected: number;
    addDialogVisible: boolean;
    tabSelected: string;
    onSelectHarmonic: (index: number) => void;
    onAddDialogClicked: () => void;
    onDeleteClicked: (index: number) => void;
    onAddClicked: () => void;
    onCancelClicked: () => void;
    onAddHarmonicChange: (newHarmonic: Harmonic) => void;
    onTabSelected: (newValue: string) => void;
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

    const styleWindow = {
        width: 1024,
        margin: 20,
        textAlign: 'left',
        display: 'inline-block',
    };

    const styleList = {
        margin: 20,
        textAlign: 'left',
        display: 'inline-block',
        verticalAlign: 'top'
    };

    let selectedHarmonic = props.harmonics[props.selected];
    let chartData = selectedHarmonic.getData([0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5]);

    return (
        <Paper style={styleWindow} zDepth={1}>
            <AppBar
                title="Chart Drawer"
                iconClassNameRight="muidocs-icon-navigation-expand-more"
            />
            <Paper style={styleList} zDepth={1} >
                <HarmonicsList
                    onSelectHarmonic={props.onSelectHarmonic}
                    harmonics={props.harmonics}
                    selected={props.selected}
                />
                <Divider />
                <RaisedButton onClick={props.onAddDialogClicked} label="Add New" />
                <RaisedButton onClick={() => {props.onDeleteClicked(props.selected); }} label="Delete Selected" />
                <AddHarmonicDialog
                    onAddClicked={props.onAddClicked}
                    onCancelClicked={props.onCancelClicked}
                    visible={props.addDialogVisible}
                    tmpHarmonic={props.tmpHarmonic}
                    onHarmonicChange={props.onAddHarmonicChange}
                />
            </Paper>
            <HarmonicsDetailed name="show" readonly={true} harmonic={selectedHarmonic} />
            <Tabs
                value={props.tabSelected}
                onChange={props.onTabSelected}
            >
                <Tab label="Line Chart" value="line">
                    <Paper style={{padding: 20}} zDepth={1}>
                        <HarmonicLineChart data={chartData} />
                    </Paper>
                </Tab>
                <Tab label="Table Chart" value="table">
                    <Paper style={{padding: 20}} zDepth={1}>
                        <HarmonicTableChart data={chartData} />
                    </Paper>
                </Tab>
            </Tabs>
        </Paper>
    );
}