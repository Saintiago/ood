import * as React from 'react';
import * as ReactDOM from 'react-dom';

import './index.css';

import { createStore } from 'redux';
import { selectHarmonic } from './reducers/ChartDrawerReducers';
import { ChartDrawerState } from './types/ChartDrawerState';

import ChartDrawerContainer from './containers/ChartDrawerContainer';
import { Provider } from 'react-redux';

import Harmonic from './components/Harmonic';
import {harmonicFunctionType} from './constants/harmonicFunctionType';

let harmonicsList = [] as Harmonic[];

harmonicsList.push(new Harmonic(4.5, 23, -1, harmonicFunctionType.Sin));
harmonicsList.push(new Harmonic(-11, 4, 1, harmonicFunctionType.Cos));
harmonicsList.push(new Harmonic(1, 1, 3, harmonicFunctionType.Sin));

const store = createStore<ChartDrawerState>(selectHarmonic, {
    harmonics: harmonicsList,
    tmpHarmonic: new Harmonic(0, 0, 0, harmonicFunctionType.Sin),
    selectedHarmonic: 0,
    addDialogVisible: false
});

ReactDOM.render(
    <Provider store={store}>
        <ChartDrawerContainer />
    </Provider>,
    document.getElementById('root') as HTMLElement
);