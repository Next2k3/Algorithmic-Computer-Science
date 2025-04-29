/*global Image, console, Prism */
/*jslint browser */

const hamMenu = document.querySelector(".ham-menu");
const navMenu = document.querySelector(".nav-menu");
const menuCheckbox = document.querySelector(".menu-checkbox");

function toggleMenu() {
    hamMenu.classList.toggle("active");
    if (hamMenu.classList.contains("active")) {
        menuCheckbox.checked = true;
        navMenu.style.display = "flex";
    } else {
        menuCheckbox.checked = false;
        navMenu.style.display = "none";
    }
}

function handleWindowResize() {
    if (window.innerWidth > 1300) {
        navMenu.style.display = "";
    } else if (
        window.innerWidth <= 1300 &&
        !menuCheckbox.checked &&
        !hamMenu.classList.contains("active")
    ) {
        navMenu.style.display = "none";
    }
}

function loadExecutor(resolve, reject, src) {
    const img = new Image();
    img.src = src;
    img.alt = "Galeria zdjęć";
    img.classList.add("gallery-item");
    img.onload = function () {
        resolve(img);
    };
    img.onerror = function () {
        reject("Błąd ładowania obrazu: " + src);
    };
}

function loadImage(src) {
    return new Promise(function (resolve, reject) {
        loadExecutor(resolve, reject, src);
    });
}

function loadGallery(images, galleryContainer) {
    const imagePromises = images.map(function (src) {
        return loadImage(src);
    });
    Promise.all(imagePromises).then(function (loadedImages) {
        loadedImages.forEach(function (image) {
            galleryContainer.appendChild(image);
        });
    }).catch(function (error) {
        console.error(error);
    });
}

hamMenu.addEventListener("click", toggleMenu);
window.addEventListener("resize", handleWindowResize);
handleWindowResize();

document.addEventListener("DOMContentLoaded", function () {
    const galleryContainer = document.getElementById("galleryContainer");
    if (galleryContainer) {
        const images = [
            "zdjecia/kot-1.jpeg",
            "zdjecia/kot-2.jpeg",
            "zdjecia/kot-3.jpeg",
            "zdjecia/kot-4.jpeg",
            "zdjecia/kot-5.jpeg",
            "zdjecia/kot-6.jpeg",
            "zdjecia/kot-7.jpeg",
            "zdjecia/kot-8.jpeg"
        ];
        loadGallery(images, galleryContainer);
    }
});

document.addEventListener("DOMContentLoaded", function () {
    if (Prism !== undefined) {
        Prism.highlightAll();
    }
});
