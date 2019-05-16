#include "settings_button.h"
#include "levelloader.h"
#include <QDebug>

SettingsButton::SettingsButton(const QString& title, qint32 width, qint32 height,  QString key,
                               QWidget* parent) :
  Button (title, width, height, parent),
  key_(key) {
  this->setFocusPolicy(Qt::ClickFocus);
}

void SettingsButton::ChangeControl(Qt::Key new_key) {
  Player::controls_map_[key_] = new_key;
}

void SettingsButton::mousePressEvent(QMouseEvent* event) {
  Button::mousePressEvent(event);
  setFocus();
}

void SettingsButton::keyReleaseEvent(QKeyEvent* event) {
  Qt::Key key = static_cast<Qt::Key>(event->key());
  int a = static_cast<int>(key);

  switch(a) {             // without "ESC", "Num Lock", "PrtScr"
    case (32): {
      setText("Space");
      break;
    }
    case (16777220): {
      setText("Enter");
      break;
    }
    case (16777221): {
      setText("NumEnter");
      break;
    }
    case (16777251): {
      setText("Alt");
      break;
    }
    case (16777248): {
      setText("Shift");
      break;
    }
    case (16777249): {
      setText("Ctrl");
      break;
    }
    case (16777217): {
      setText("Tab");
      break;
    }
    case(16777264): {
      setText("F1");
      break;
    }
    case(16777265): {
      setText("F2");
      break;
    }
    case(16777266): {
      setText("F3");
      break;
    }
    case(16777267): {
      setText("F4");
      break;
    }
    case(16777268): {
      setText("F5");
      break;
    }
    case(16777269): {
      setText("F6");
      break;
    }
    case(16777270): {
      setText("F7");
      break;
    }
    case(16777271): {
      setText("F8");
      break;
    }
    case(16777272): {
      setText("F9");
      break;
    }
    case(16777273): {
      setText("F10");
      break;
    }
    case(16777274): {
      setText("F11");
      break;
    }
    case(16777275): {
      setText("F12");
      break;
    }
    case(16777222): {
      setText("Insert");
      break;
    }
    case(16777223): {
      setText("Delete");
      break;
    }
    case(16777238): {
      setText("PgUp");
      break;
    }
    case(16777239): {
      setText("PgDn");
      break;
    }
    case(16777232): {
      setText("Home");
      break;
    }
    case(16777233): {
      setText("End");
      break;
    }
    case(16777235): {
      setText("🡹");
      break;
    }
    case(16777234): {
      setText("🡸");
      break;
    }
    case(16777237): {
      setText("🡻");
      break;
    }
    case(16777236): {
      setText("🡺");
      break;
    }
    case(16777219): {
      setText("Backspace");
      break;
    }
    default: {
      if (event->text().isEmpty()) return;
      setText(event->text().toUpper());
    }
  }

  ChangeControl(key);
  this->clearFocus();
  emit Changed();
}
