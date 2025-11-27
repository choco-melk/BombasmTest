import addTypeWriterEffect from './../global.js'

(async () => {
    await addTypeWriterEffect(".desc", "Welcome to the Tutorial Levels :)")
})()

document.querySelector(".home-btn").addEventListener("click", e => {
    e.preventDefault();
    window.location.href = "./../"
})
document.querySelector(".prev-btn").addEventListener("click", e => {
    e.preventDefault();
    window.location.href = "./../puzzle-levels/"
})

document.querySelectorAll(".level-btn").forEach(element => {
    element.addEventListener("click", e => {
        e.preventDefault();
        window.location.href = "./../tutorial/"
    });
});

TutorialLevelsModule().then((Module) => {
    const tutorialLevelDisplay = document.querySelector(".levels");
    const getLevelCount = Module.cwrap("getTutorialLevelCount", "number", []);
    const getLevelDesc = Module.cwrap("getTutorialLevelDescription", "string", ["number"])
    const getLevelOperator = Module.cwrap("getTutorialLevelOperator", "string", ["number"]);
    for (let i = 0; i < getLevelCount(); i++) {
        const button = document.createElement("button");
        button.className = "level-btn";
        button.textContent = getLevelOperator(i);
        button.addEventListener("click", () => {
            window.location.href= `./../tutorial/?level=${i}`;
        });
        button.addEventListener("mouseover", async () => {
            await addTypeWriterEffect(".desc", getLevelDesc(i))
        })
        tutorialLevelDisplay.appendChild(button);
    }
});


