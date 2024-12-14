var __classPrivateFieldSet = (this && this.__classPrivateFieldSet) || function (receiver, state, value, kind, f) {
    if (kind === "m") throw new TypeError("Private method is not writable");
    if (kind === "a" && !f) throw new TypeError("Private accessor was defined without a setter");
    if (typeof state === "function" ? receiver !== state || !f : !state.has(receiver)) throw new TypeError("Cannot write private member to an object whose class did not declare it");
    return (kind === "a" ? f.call(receiver, value) : f ? f.value = value : state.set(receiver, value)), value;
};
var __classPrivateFieldGet = (this && this.__classPrivateFieldGet) || function (receiver, state, kind, f) {
    if (kind === "a" && !f) throw new TypeError("Private accessor was defined without a getter");
    if (typeof state === "function" ? receiver !== state || !f : !state.has(receiver)) throw new TypeError("Cannot read private member from an object whose class did not declare it");
    return kind === "m" ? f : kind === "a" ? f.call(receiver) : f ? f.value : state.get(receiver);
};
var _LocalStorageGameStorage_storageKey, _GameLogic_secretNumber, _GameLogic_storage, _GameLogic_gameData, _GameUIAdapter_logic, _GameUIAdapter_domService;
// データの永続化 localStorageはweb APIで定義されているグローバルオブジェクト
var LocalStorageGameStorage = /** @class */ (function () {
    function LocalStorageGameStorage(storageKey) {
        if (storageKey === void 0) { storageKey = 'my-game'; }
        _LocalStorageGameStorage_storageKey.set(this, void 0);
        __classPrivateFieldSet(this, _LocalStorageGameStorage_storageKey, storageKey, "f");
        localStorage.setItem('count', 0);
    }
    LocalStorageGameStorage.prototype.save = function (data) {
        localStorage.setItem(__classPrivateFieldGet(this, _LocalStorageGameStorage_storageKey, "f"), JSON.stringify(data));
    };
    LocalStorageGameStorage.prototype.load = function () {
        var data = localStorage.getItem(this.storageKey);
        return data ? JSON.parse(data) : [];
    };
    LocalStorageGameStorage.prototype.getCount = function () {
        return localStorage.getItem(this.storageKey, 'count');
    };
    return LocalStorageGameStorage;
}());
_LocalStorageGameStorage_storageKey = new WeakMap();
// DOM操作の抽象化を行う
var GameDomService = /** @class */ (function () {
    function GameDomService() {
        this.inputNumForm = document.getElementById("inputNumForm");
        this.info = document.getElementById("info");
        this.inputNum = document.getElementById("input_num");
    }
    GameDomService.prototype.getInputNum = function () {
        return Number(this.inputNum.value);
    };
    GameDomService.prototype.setReply = function (reply) {
        info.textContent = reply;
    };
    GameDomService.prototype.setAddInputListener = function (callback) {
        this.inputNumForm.addEventListener('submit', callback);
    };
    return GameDomService;
}());
// 状態管理やロジックを管理する一番核となる部分。CUIだけならここのロジックだけで動く感じ。
var GameLogic = /** @class */ (function () {
    function GameLogic(storage, secretNumber) {
        _GameLogic_secretNumber.set(this, void 0);
        _GameLogic_storage.set(this, void 0);
        _GameLogic_gameData.set(this, void 0);
        __classPrivateFieldSet(this, _GameLogic_secretNumber, secretNumber, "f");
        __classPrivateFieldSet(this, _GameLogic_storage, storage, "f");
        __classPrivateFieldSet(this, _GameLogic_gameData, __classPrivateFieldGet(this, _GameLogic_storage, "f").load(), "f");
    }
    GameLogic.prototype.checkNumber = function (number) {
        var data = {
            'number': number
        };
        __classPrivateFieldGet(this, _GameLogic_gameData, "f").push(data);
        __classPrivateFieldGet(this, _GameLogic_storage, "f").save(__classPrivateFieldGet(this, _GameLogic_gameData, "f"));
        return (__classPrivateFieldGet(this, _GameLogic_secretNumber, "f") === number) ? true : false;
    };
    GameLogic.prototype.createReply = function (isNumCorrect, number) {
        if (isNumCorrect) {
            return "".concat(__classPrivateFieldGet(this, _GameLogic_secretNumber, "f"), " is the secret number. Count is ").concat(Object.keys(__classPrivateFieldGet(this, _GameLogic_gameData, "f")).length);
        }
        else {
            return "".concat(number, " is not correct. Count is ").concat(Object.keys(__classPrivateFieldGet(this, _GameLogic_gameData, "f")).length);
        }
    };
    return GameLogic;
}());
_GameLogic_secretNumber = new WeakMap(), _GameLogic_storage = new WeakMap(), _GameLogic_gameData = new WeakMap();
// 抽象化されたUIのイベントにロジックを割り当てるアダプター。
var GameUIAdapter = /** @class */ (function () {
    function GameUIAdapter(logic, domService) {
        var _this = this;
        _GameUIAdapter_logic.set(this, void 0);
        _GameUIAdapter_domService.set(this, void 0);
        __classPrivateFieldSet(this, _GameUIAdapter_logic, logic, "f");
        __classPrivateFieldSet(this, _GameUIAdapter_domService, domService, "f");
        __classPrivateFieldGet(this, _GameUIAdapter_domService, "f").setAddInputListener(function () {
            event.preventDefault();
            var number = __classPrivateFieldGet(_this, _GameUIAdapter_domService, "f").getInputNum();
            var check = __classPrivateFieldGet(_this, _GameUIAdapter_logic, "f").checkNumber(number);
            var reply = __classPrivateFieldGet(_this, _GameUIAdapter_logic, "f").createReply(check, number);
            __classPrivateFieldGet(_this, _GameUIAdapter_domService, "f").setReply(reply);
        });
    }
    return GameUIAdapter;
}());
_GameUIAdapter_logic = new WeakMap(), _GameUIAdapter_domService = new WeakMap();
// アプリケーションの初期化と依存性注入(Dependency Injection)
var GameApp = /** @class */ (function () {
    function GameApp() {
    }
    GameApp.initialize = function () {
        var secretNumber = 49;
        var storage = new LocalStorageGameStorage('my-game');
        var domService = new GameDomService();
        var gameLogic = new GameLogic(storage, secretNumber);
        var gameUIAdapter = new GameUIAdapter(gameLogic, domService);
        return {
            logic: gameLogic,
            adapter: gameUIAdapter
        };
    };
    return GameApp;
}());
var app = GameApp.initialize();
