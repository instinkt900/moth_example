# moth_example — Revamp Plan

## Goal

A self-contained interactive demo that walks through the features of both `moth_ui` and `moth_graphics`. Each feature gets its own screen. The user navigates between screens with arrow buttons (or keyboard). Every screen plays an entrance animation so the animation system is always visible.

---

## Application Flow

```
Startup
  └─ ExampleApplication creates Window + ExampleLayer
       └─ ExampleLayer loads "screens/title.mothui"
            └─ plays "intro" clip
                 └─ when "intro" stops → plays "idle" clip (loops)

User clicks Next / presses Right arrow
  └─ current screen plays "transition_out"
       └─ when "transition_out" stops → load next screen, play "transition_in"
            └─ when "transition_in" stops → plays "idle" clip (loops)

User clicks Prev / presses Left arrow
  └─ same as above, in reverse order
```

The navigation chrome (arrow buttons, page indicator dots, screen title) is a persistent overlay layer sitting on top of the current screen layer.

---

## Screen List

### 0 — Title
**Shows:** application startup, text nodes, intro animation, font usage.

Content:
- Large title text: "moth" with a drop shadow
- Subtitle: "a 2D UI framework"
- Version string bottom-right
- Background: animated colour wash (color track, Loop clip)

Clips: `intro` (rect + text fade in, BounceOut easing), `idle` (subtle pulse on title).

---

### 1 — Nodes
**Shows:** all five node types side by side with labels.

Content:
- `NodeRect` — filled and outlined variants
- `NodeImage` — three scale modes: Stretch / Tile / NineSlice (same image, three instances)
- `NodeText` — all nine alignment combinations in a 3×3 grid
- `NodeClip` — an oversized image inside a clip rect, scrolling via a Loop animation track on LeftOffset

Clips: `intro` (each panel slides in with a stagger delay), `idle` (clip-scroll loop on NodeClip panel).

Assets: one tileable texture (e.g. a small checkerboard), one nineslice panel image.

---

### 2 — Animation
**Shows:** keyframe tracks, easing types, named clips, animation events.

Content:
- A row of eight small coloured rects — each assigned a different `InterpType` (Linear, SineInOut, BounceOut, ElasticOut, BackOut, QuartInOut, CircOut, Step)
- Label below each rect with the easing name
- All rects animate the same property (TopOffset) simultaneously so the difference is visible
- An "event fired" text node that appears briefly when a named `AnimationEvent` fires mid-clip

Buttons: "Play", "Loop", "Reset" — each triggers `SetAnimation()` with a different clip.

Clips: `demo_stop` (plays once, stops), `demo_loop` (loops), `demo_reset` (plays, resets to frame 0).

---

### 3 — Events
**Shows:** mouse events, key events, event bubbling, custom event handlers.

Content:
- A large target button with three concentric zones (outer Group → middle Group → inner Rect)
  - Each zone lights up a different colour on hover and click
  - Labels show which zone received the event — demonstrates bubbling vs. consumption
- A keyboard display: last key pressed shown as text
- A mouse position readout (updated via EventMouseMove)

No clips needed; this screen is fully interactive. `intro` / `idle` apply to the panel chrome only.

---

### 4 — Layouts
**Shows:** sub-layout references (`LayoutEntityRef`), anchor/offset resolution independence.

Content:
- A reusable "card" component defined in `screens/components/card.mothui`
  - Contains: thumbnail image, title text, body text, coloured border
  - Three instances of the card referenced into the main layout at different sizes
- A resize demonstration: slider (or buttons) that changes the window render size between preset
  resolutions (480×270, 960×540, 1920×1080) — card layouts reflow without distortion, showing
  that anchor fractions maintain proportions

Clips: `intro` (cards slide in with stagger), `idle` (none needed).

Assets: three placeholder thumbnail images.

---

### 5 — Flipbook
**Shows:** `NodeFlipbook`, sprite sheets, discrete animation tracks, `FlipbookClip` / `FlipbookPlaying`.

Content:
- A character or icon sprite sheet with at least two named clips (e.g. `walk`, `idle`)
- The flipbook node centred on screen, large enough to see clearly
- Buttons: "Walk", "Idle" — each calls `SetAnimation()` on the group, which drives the
  `FlipbookClip` discrete track to switch the active clip
- Loop type shown as a text label that updates when the clip changes (via `EventAnimationStarted`)

Clips: `intro` (flipbook fades in), `idle` (none — flipbook manages its own playback).

Assets: one sprite sheet (PNG) + one flipbook descriptor JSON, produced by moth_packer or authored
by hand. Minimum 8 frames per clip; two clips.

---

## Persistent Chrome Layer

A second `Layer` sits above all screen layers. It always draws:

- Left arrow button (`<`) — disabled and greyed out on the first screen
- Right arrow button (`>`) — disabled and greyed out on the last screen
- Row of dot indicators (one per screen; current screen dot filled)
- Screen title text top-left

The chrome layer is a single layout loaded once: `screens/chrome.mothui`.
Buttons are `UIButton` custom widgets. The dot indicators are `NodeRect` nodes toggled visible/invisible.

---

## Code Structure

```
moth_example/
  src/
    main.cpp                  — creates ExampleApplication, sets layout root, runs loop
    example_application.h/cpp — extends Application; sets up Context, chrome layer, screen layer
    example_layer.h/cpp       — base layer: Load/transition logic, OnAnimationStopped dispatch
    chrome_layer.h/cpp        — persistent nav chrome; owns current screen index, fires Next/Prev
    screens/
      screen_title.h/cpp      — title screen (currently: demo.mothui placeholder)
      screen_nodes.h/cpp
      screen_animation.h/cpp
      screen_events.h/cpp
      screen_layouts.h/cpp
      screen_flipbook.h/cpp
    widgets/
      ui_button.h/cpp         — existing UIButton widget (keep as-is)
      ui_dot.h/cpp            — dot indicator widget (NodeRect subclass, toggled active/inactive)
  assets/
    fonts/                    — existing fonts (trim to 2–3 used ones)
    images/
      checkerboard.png         — small tileable texture for Nodes screen
      nineslice_panel.png      — panel with defined border slices
      card_thumb_1.png         — placeholder thumbnails (×3)
      card_thumb_2.png
      card_thumb_3.png
    sprites/
      character.png            — sprite sheet for Flipbook screen
      character.json           — flipbook descriptor (moth_packer output)
    layouts/
      screens/
        title.mothui
        nodes.mothui
        animation.mothui
        events.mothui
        layouts.mothui
        flipbook.mothui
        chrome.mothui
        components/
          card.mothui
```

---

## What Each Library Gets Credit For

| Feature demonstrated | Library |
|---|---|
| Node types (Rect, Image, Text, Clip, Group) | moth_ui |
| Animation tracks + easing | moth_ui |
| Named clips, LoopType, AnimationEvents | moth_ui |
| Event system (mouse, key, bubbling) | moth_ui |
| Sub-layout references + anchor/offset | moth_ui |
| Custom widgets (CRTP Widget<T>) | moth_ui |
| Layer stack, layer transitions | moth_ui |
| Flipbook / sprite animation | moth_ui |
| Window creation, event loop | moth_graphics |
| SDL/Vulkan renderer backend | moth_graphics |
| Image loading, font loading | moth_graphics |
| IGraphics / MothRenderer bridge | moth_graphics |
| Sprite sheet + moth_packer integration | moth_graphics + moth_packer |

---

## Out of Scope

- Sound / music
- Networking
- Save/load of user state
- More than one window
- ImGui (editor-only dependency)
