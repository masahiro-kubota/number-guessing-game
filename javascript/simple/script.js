// inputNumFormのsubmitボタンが押されるとhanlerFormSubmitがイベントコールされる 
// eventは送信されたeventオブジェクト
document.getElementById("inputNumForm").addEventListener("submit", handleFormSubmit);

function handleFormSubmit(event){
  event.preventDefault();
  console.log(event.type);
}

    
