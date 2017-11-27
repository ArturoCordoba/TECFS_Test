//
// Created by arturocv on 26/11/17.
//

#include "VideoPlayerWindow.h"

int VideoPlayerWindow::render(std::string fileName) {
    std::cout << "Shortcuts:\n"
              << "\tSpace - Play / pause\n"
              << "\tH - Hide / show user controls and mouse cursor\n"
              << "\tF - Toggle fullscreen\n";

    sfe::Movie movie;
    if (!movie.openFromFile(fileName)) {
        return 1;
    }

    bool fullscreen = false;
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    float width = std::min(static_cast<float>(desktopMode.width), movie.getSize().x);
    float height = std::min(static_cast<float>(desktopMode.height), movie.getSize().y);

    // For audio files, there is no frame size, set a minimum:
    if (width * height < 1.f) {
        width = std::max(width, 250.f);
        height = std::max(height, 40.f);
    }

    // Create window
    sf::RenderWindow window(sf::VideoMode(width, height), "Video Player",
                            sf::Style::Close | sf::Style::Resize);

    // Scale movie to the window drawing area and enable VSync
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    movie.fit(0, 0, width, height);

    UserInterface ui(window, movie);
    StreamSelector selector(movie);

    movie.play();

    while (window.isOpen())
    {
        sf::Event ev;
        while (window.pollEvent(ev))
        {
            // Window closure
            if (ev.type == sf::Event::Closed ||
                (ev.type == sf::Event::KeyPressed &&
                 ev.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }

            if (ev.type == sf::Event::KeyPressed)
            {
                switch (ev.key.code)
                {
                    case sf::Keyboard::Space:
                        if (movie.getStatus() == sfe::Playing)
                            movie.pause();
                        else
                            movie.play();
                        break;

                    case sf::Keyboard::F:
                        fullscreen = !fullscreen;

                        if (fullscreen)
                            window.create(desktopMode, "sfeMovie Player", sf::Style::Fullscreen);
                        else
                            window.create(sf::VideoMode(width, height), "sfeMovie Player",
                                          sf::Style::Close | sf::Style::Resize);

                        window.setFramerateLimit(60);
                        window.setVerticalSyncEnabled(true);
                        movie.fit(0, 0, (float)window.getSize().x, (float)window.getSize().y);
                        ui.applyProperties();
                        break;

                    case sf::Keyboard::H:
                        ui.toggleVisible();
                        break;

                    default:
                        break;
                }
            }
            else if (ev.type == sf::Event::MouseWheelMoved)
            {
                float volume = movie.getVolume() + 10 * ev.mouseWheel.delta;
                volume = std::min(volume, 100.f);
                volume = std::max(volume, 0.f);
                movie.setVolume(volume);
            }
            else if (ev.type == sf::Event::Resized)
            {
                movie.fit(0, 0, window.getSize().x, window.getSize().y);
                window.setView(sf::View(sf::FloatRect(0, 0, (float)window.getSize().x, (float)window.getSize().y)));
            }
            else if (ev.type == sf::Event::MouseButtonPressed ||
                     (ev.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
            {
                int xPos = 0;

                if (ev.type == sf::Event::MouseButtonPressed)
                    xPos = ev.mouseButton.x;
                else if (ev.type == sf::Event::MouseMoved)
                    xPos = ev.mouseMove.x;

                float ratio = static_cast<float>(xPos) / window.getSize().x;
                sf::Time targetTime = ratio * movie.getDuration();
                movie.setPlayingOffset(targetTime);
            }
        }

        movie.update();

        // Render movie
        window.clear();
        window.draw(movie);
        ui.draw();
        window.display();
    }

    return 0;
}
