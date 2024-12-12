class Game{
  constructor(secret_number){
    this._secret_number = secret_number;
  }

  get secret_number(){
    return this._secret_number;
  }
}





function handleFormSubmit(event){
  event.preventDefault();
  const info = document.getElementById("info");
  const input_num  = document.getElementById("input_num").value;
  if (input_num == game.secret_number) {
    info.textContent = `${input_num} is secret number`;
  } else {
    info.textContent = `${input_num} is not secret number`;
  }
}

let game;

function main(){
  game = new Game(49);
  // inputNumFormのsubmitボタンが押されるとhanlerFormSubmitがイベントコールされる 
  // eventは送信されたeventオブジェクト
 document.getElementById("inputNumForm").addEventListener("submit", handleFormSubmit);
}

window.addEventListener("DOMContentLoaded", main);
