<script lang='ts'>
import { ComparisonResult } from './enums/ComparisonResult';
import { numberInput } from './types/index';
import { GameLogic } from './logic/GameLogic';
import { LocalStorageGameStorage } from './logic/GameStorage'; 

export default {
  data(): {gameLogic: GameLogic | null, storage: LocalStorageGameStorage | null, reply: string, inputNum: number | null} {
    return {
      gameLogic: null,
      storage: null,
      reply: 'Enter a number',
      inputNum: null,
    }
  },
  mounted() {
    const secretNumber: number = 49;
    const maxCount: number = 7;
    this.storage = new LocalStorageGameStorage('my-game');
    this.gameLogic = new GameLogic(this.storage, secretNumber, maxCount);
  },
  methods: {
    handleSubmit() {
      console.log(this.secretNumber);
      this.reply = this.gameLogic.checkInput(this.inputNum);
      this.inpuNum = 0; 
    },
    handleReset() {
      console.log('test2');
      if (!this.gameLogic) return;
      this.gameLogic.restartGame();
      this.reply = 'Reset';
      this.inputNum = 0;
    }
  }
}

</script>

<template>
  <div>
    <h1>Number Guessing Game</h1>
    <form @submit.prevent='handleSubmit' class='space-x-4'>
      <input v-model='inputNum' placeholder='e.g., 99' required>
      <button type='submit' class='bg-blue-500'>Submit</button>
    </form>
    <div>
        <p>{{ reply }}</p>
    </div>
    <button @click='handleReset' class='bg-blue-500'>Reset Attempts</button>
  </div>
</template>

