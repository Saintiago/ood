import * as React from 'react';
import Harmonic from './Harmonic';
import HarmonicsList from './HarmonicsList';
import HarmonicsDetailed from './HarmonicDetailed';
import AddHarmonicDialog from './AddHarmonicDialog';
import HarmonicLineChart from './HarmonicLineChart';
import HarmonicTableChart from './HarmonicTableChart';
import {RaisedButton, AppBar, Paper, Tabs, Tab } from 'material-ui';
import * as style from '../constants/styles';

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
            <Paper style={style.main_window} zDepth={1}>
                <AppBar
                    title="Chart Drawer"
                    iconClassNameRight="muidocs-icon-navigation-expand-more"
                />
                <RaisedButton onClick={props.onAddDialogClicked} label="Add New" style={style.empty_list_add} />
                <AddHarmonicDialog
                    onAddClicked={props.onAddClicked}
                    onCancelClicked={props.onCancelClicked}
                    visible={props.addDialogVisible}
                    tmpHarmonic={props.tmpHarmonic}
                    onHarmonicChange={props.onAddHarmonicChange}
                />
            </Paper>
        );
    }

    let selectedHarmonic = props.harmonics[props.selected];
    let chartData = selectedHarmonic.getData([0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5]);

    return (
        <Paper style={style.main_window} zDepth={1}>
            <AppBar
                title="Chart Drawer"
                iconClassNameRight="muidocs-icon-navigation-expand-more"
            />
            <Paper style={style.harmonic_list} zDepth={0}>
                <HarmonicsList
                    onSelectHarmonic={props.onSelectHarmonic}
                    harmonics={props.harmonics}
                    selected={props.selected}
                />
                <RaisedButton onClick={props.onAddDialogClicked} label="Add New" />
                <RaisedButton
                    onClick={() => {props.onDeleteClicked(props.selected); }}
                    label="Delete Selected"
                />
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
                style={style.tabs}
                value={props.tabSelected}
                onChange={props.onTabSelected}
            >
                <Tab label="Line Chart" value="line">
                    <div style={style.chart}>
                        <HarmonicLineChart data={chartData} />
                    </div>
                </Tab>
                <Tab label="Table Chart" value="table">
                    <div style={style.chart}>
                        <HarmonicTableChart data={chartData} />
                    </div>
                </Tab>
            </Tabs>
        </Paper>
    );
}