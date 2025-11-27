import addTypeWriterEffect from './../global.js'

(async () => {
    await addTypeWriterEffect(".desc", "Welcome to the Tutorial Levels :)")
})()

document.querySelector(".home-btn").addEventListener("click", e => {
    e.preventDefault();
    window.location.href = "../index.html"
})
document.querySelector(".prev-btn").addEventListener("click", e => {
    e.preventDefault();
    window.location.href = "../puzzle-levels/index.html"
})

document.querySelectorAll(".level-btn").forEach(element => {
    element.addEventListener("click", e => {
        e.preventDefault();
            window.location.href = "../tutorial/index.html"
    });
});

TutorialLevelsModule().then((Module) => {
    const tutorialLevelDisplay = document.querySelector(".levels");
    const getLevelCount = Module.cwrap("getTutorialLevelCount", "number", []);
    const getLevelDesc = Module.cwrap("getTutorialLevelDescription", "string", ["number"])
    const getLevelOperator = Module.cwrap("getTutorialLevelOperator", "string", ["number"]);
    const getLeveTitle = Module.cwrap("getTutorialLevelTitle", "string", ["number"]);

    for (let i = 0; i < getLevelCount(); i++) {
        const button = document.createElement("button");
        button.className = "level-btn";
        button.textContent = getLevelOperator(i);
        button.addEventListener("click", () => {
            window.location.href= `../tutorial/index.html?level=${i}`;
        });
        button.addEventListener("mouseover", async () => {
            await addTypeWriterEffect(".desc", getLeveTitle(i))
        })
        tutorialLevelDisplay.appendChild(button);
    }
});


