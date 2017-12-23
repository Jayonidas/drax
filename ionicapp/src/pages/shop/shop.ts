import { Component } from '@angular/core';
import { IonicPage, NavController, NavParams } from 'ionic-angular';

/**
 * Generated class for the ShopPage page.
 *
 * See https://ionicframework.com/docs/components/#navigation for more info on
 * Ionic pages and navigation.
 */

@IonicPage()
@Component({
  selector: 'page-shop',
  templateUrl: 'shop.html',
})
export class ShopPage {

  constructor(public navCtrl: NavController, public navParams: NavParams) {
  }

  openCloseBlastGate(gateID, open){

    var ip = "192.168.1.23";

    var url = "http://"+ip+"/openBlastGate?gate="+gateID+"&open="+open;
    fetch(url);

  }

  ionViewDidLoad() {
    console.log('ionViewDidLoad ShopPage');
  }

}
