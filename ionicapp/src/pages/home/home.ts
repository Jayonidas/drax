import { Component } from '@angular/core';
import { NavController } from 'ionic-angular';

@Component({
  selector: 'page-home',
  templateUrl: 'home.html'
})
export class HomePage {

  constructor(public navCtrl: NavController) {

  }

  relayOn(){

  	var xhr = new XMLHttpRequest();
  	xhr.open('GET', "http://192.168.1.23/RELAY=OFF", true);
  	xhr.send();

  }

  relayOff(){

  	var xhr = new XMLHttpRequest();
  	xhr.open('GET', "http://192.168.1.23/RELAY=ON", true);
  	xhr.send();

  }

}
