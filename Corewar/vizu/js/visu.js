"use strict";

//interface colors tracker
var clrs = {
    blue : "rgb(0,110,255)",   //blue
    green : "rgb(15,185,0)",   //green
    red : "rgb(230,0,0)",      //red
    purple : "rgb(230,0,230)", //purple
    yellow : "rgb(250,250,0)", //yellow
    grey : "rgb(80,80,80)"  //grey
};

var text_mode = true;
var block_mode = true;
var text_mode_bold = false;
var arena_block_clr = clrs.grey;
var player_clrs = [clrs.blue, clrs.red, clrs.green, clrs.purple, clrs.yellow];
var arena_block_shape = ['round', 1];
var player_shapes = [['square', 2], ['square', 2], ['square', 2], ['square', 2], ['square', 2]];
var uri = "127.0.0.1";
var port = "8082";
var address = "ws://" + uri + ":" + port;
var ws;

//global variables
var title;
var canvas;
var mem_div;
var cmd_div;
var back_img;
var joystix_font;
var str;
var trim;
var fontsize;
var block = [];
var start_x = 557;
var start_y = 35;
var itx = 0;
var ity = 0;
var space_x = 20.7;
var space_y = 14.4;

//core GET variables
var player = [];
var in_set = [];
var in_cyc = [];
var in_exe = [];
var in_hex;
var in_map;

//min max of array as .this function
Array.prototype.max = function(){
    return Math.max.apply(null, this);
};

Array.prototype.min = function(){
    return Math.min.apply(null, this);
};

String.prototype.rpl = function(from, to) {
    let target = this;
    return target.replace(new RegExp(from, 'g'), to);
};

//canvas resize on viewport change
function canvas_resize(){
    win.w = Math.max(document.documentElement.clientWidth, window.innerWidth || 0);
    win.h = Math.max(document.documentElement.clientHeight, window.innerHeight || 0);
    resizeCanvas(win.w, win.h, true);
}
//viewport size tracker
var win = {
    w : Math.max(document.documentElement.clientWidth, window.innerWidth || 0),
    h : Math.max(document.documentElement.clientHeight, window.innerHeight || 0),
};

class Block{
    constructor(x, y, player){
        this.x = x;
        this.y = y;
        this.shape = player ? player.shape : arena_block_shape;
        this.clr = player ? player.clr : arena_block_clr;
        this.player = player ? player : null;
        //console.log(this.clr);
    }
    set_player(player){
        if (typeof player !== 'undefined'){
            this.player = player;
            this.shape = player.shape;
            this.clr = player.clr;
        }
    }
    draw(){
        fill(this.clr);
        switch (this.shape[0]){
            case 'square' :
                rect(this.x, this.y, space_x-this.shape[1], space_y-this.shape[1]);
                break;
            case 'round' :
                ellipse(this.x, this.y, space_x-this.shape[1], space_y-this.shape[1]);
                break;
            case 'triangle' :
                triangle(this.x - space_x/2, this.y-space_y/2+(space_y-this.shape[1]),
                this.x-space_x/2+((space_x-this.shape[1])/2), this.y-space_y/2,
                this.x-space_x/2+(space_x-this.shape[1]), this.y-space_y/2+(space_y-this.shape[1]));
                break;
        }
    }
};

//Player shapes: square / triangle / round

class Player{
    constructor(name, msg, clr, shape){
        this.name = name;
        this.msg = msg;
        this.clr = clr;
        this.shape = shape;
        console.log("New player:", this.name);
    }
    set_name(name){
        this.name = name;
    }
    get_name(){
        return this.name;
    }
};

//initialization function
function preload(){
    back_img = loadImage("../assets/corewar_background_2.png");
    joystix_font = loadFont("../fonts/joystix_monospace.ttf");
    title = document.getElementById('title');
    mem_div = document.getElementById("mem");
    init();
}

function init()
{
    ws = new ReconnectingWebSocket(address);
    if (window.WebSocket === undefined)
        console.log("Error: WebSockets not supported");
    //callbacks:
    ws.onopen = function(event){
        console.log("Access to WebSocket " + address + " granted");
    };

    ws.onmessage = function(event){
        let data = event.data;
        let type = data.slice(0, 5);
        //console.log(event.data);
        //console.log("Rec:" + type);
        switch (type){
            case "<set>":
                in_set = JSON.parse(data.slice(5, data.length));
                init_players();
                break;
            case "<cyc>":
                in_cyc = JSON.parse(data.slice(5, data.length));
                // update_cycles();
                break;
            case "<exe>":
                in_exe = JSON.parse(data.slice(5, data.length));
                // update_procs();
                break;
            case "<hex>":
                in_hex = data.slice(5, data.length);
                // update_hexdump();
                break;
            case "<map>": in_map = data.slice(5, data.length);
                update_ownership();
                break;
        }
    };
    ws.onclose = function(){
        console.log("WebSocket " + address + " closed");
    };
    ws.onerror = function(event){
        console.log("Communication error with " + address);
        console.log(event);
    };
}

function init_blocks(){
    for (let i = 0; i < 4096; i++){
        block[i] = new Block(start_x + (itx % 1326), start_y + (ity % 926), null);
        itx = itx > 1290 ? 0 : itx + space_x;
        ity = itx == 0 ? ity + space_y : ity;
        //if (i > 2023 && i < 3000) block[i].clr = clrs.red;
        // if (i >= (64 * 32) && i < (64 * 40)) block[i].clr = clrs.blue;
        // if (i >= (64 * 0) && i < (64 * 8)) block[i].clr = clrs.green;
    }
}
function init_players(){
    for(let i = 0; i < in_set.length; i++){
        player[i] = new Player(in_set[i], "insert_warcry", player_clrs[i], player_shapes[i]);
    }
}

function update_cycles(){
    //hori,verti
    textAlign(LEFT, CENTER);
    // textFont('Courier New');
    textFont(joystix_font);
    // textStyle(BOLD);
    textSize(30);
    fill(255,255,255,255);
    let cyc_tot = in_cyc[0];
    let cyc_td = in_cyc[1];
    if (typeof in_cyc !== 'undefined' || in_cyc.length == 0){
        cyc_tot = "Total : " + in_cyc[0];
        cyc_td = "To Die: " + in_cyc[1];
    }
    else{
        cyc_tot = "-";
        cyc_td = "-";
    }
    text(cyc_tot, 88, 425);
    text(cyc_td, 88, 455); 
}

function update_blocks(){
    if (block_mode == true){
        //update_clrs();
        for (let i = 0; i < 4096; i++){
            block[i].draw();
        }
    }
}

function update_ownership(){
    if (block_mode == true){
        //update_clrs();
        if (typeof in_map !== 'undefined' || in_map.length == 0)
            for (let i = 0; i < 4096; i++){
                block[i].set_player(player[parseInt(in_map[i]) - 1]);
            }
    }
}

function update_hexdump(){
    if (text_mode == true){
        textAlign(LEFT, TOP);
        textFont('Courier New');
        text_mode_bold ? textStyle(BOLD) : textStyle(NORMAL);
        textSize(11.5);
        // str = mem_div.innerHTML;
        // trim = str.rpl(/0x0.*: /, '')
        fill(255,255,255,200);
        text(in_hex, 550, 28); //win.w * 18 / 20, win.h * 18 / 20);
    }
}

function update_names(){
    // textAlign(CENTER, CENTER);
    // textFont('Courier New');
    // textFont('Joystix Monospace');
    // textStyle(BOLD);
    // textSize(30);
    // fill(255,255,255,255);
    // let names = "";
    // if (typeof in_set !== 'undefined'){
    //     for(let i = 0; i < in_set.length; i++){
    //         if (typeof player[i].name !== 'undefined')
    //             names += (player[i].name + "\n");
    //         else
    //             names += "unknown";
    //     }
    // }
    // else
    //     names = "unknown";
    // text(names, 1213, 950);
}

function setup(){
    //noLoop();

    frameRate(30);
    canvas = createCanvas(1920, 1000); //WEBGL);
    rectMode(CENTER);
    noStroke();
    init_blocks();
}

function draw(){
    //canvas_resize();
    background(0);
    //print player names
    //initiate font for arena printing
    background(back_img);
    update_names();
    update_blocks();
    update_hexdump();
    update_cycles();
    //...
}
