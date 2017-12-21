import { NgModule } from '@angular/core';
import { IonicPageModule } from 'ionic-angular';
import { ThermostatPage } from './thermostat';

@NgModule({
  declarations: [
    ThermostatPage,
  ],
  imports: [
    IonicPageModule.forChild(ThermostatPage),
  ],
})
export class ThermostatPageModule {}
