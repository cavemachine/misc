(require 'package)
(add-to-list 'package-archives '("melpa" . "https://melpa.org/packages/") t)
(package-initialize)
(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(custom-enabled-themes '(myGreenTheme3))
 '(custom-safe-themes
   '("d65bda5cd2b0b9fa2beab22628068d7375ed271b1e2169bc954ccf15e4b84054" default)))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(default ((t (:inherit nil :extend nil :stipple nil :background "#010101" :foreground "#007700" :inverse-video nil :box nil :strike-through nil :overline nil :underline nil :slant normal :weight normal :height 158 :width normal :foundry "V.R." :family "Px437 Wang Pro Mono"))))
 '(cursor ((t (:background "#008800" :weight normal))))
 '(font-lock-string-face ((t (:foreground "#008766" :weight normal))))
 '(show-paren-match ((t (:background "#aa9944" :weight normal)))))

(add-to-list 'custom-theme-load-path "~/.emacs.d/themes/") 
;;(global-set-key (kbd "<ESC>") 'keyboard-quit)
(global-set-key (kbd "<ESC> <ESC>") 'keyboard-escape-quit)
;;(global-set-key [?\e]      'keyboard-escape-quit)

(global-set-key [f5] 'elpy-folding-toggle-at-point)
(global-set-key [f8] 'other-window)
(global-set-key [f10] 'toggle-menu-bar-mode-from-frame)
(global-set-key [f12] 'delete-other-windows)
(global-set-key [f6] 'enlarge-window)
(global-set-key [C-f6] 'shrink-window)
(global-set-key [f7] 'enlarge-window-horizontally)
(global-set-key [C-f7] 'shrink-window-horizontally)

(defalias 'yes-or-no-p 'y-or-n-p)
(setq scroll-step 1) ;; keyboard scroll one line at a time
(scroll-bar-mode -1)

(elpy-enable)
(setq elpy-rpc-virtualenv-path 'current)
(add-hook 'prog-mode-hook #'hs-minor-mode)
(company-quickhelp-mode)
(advice-add 'elpy-shell-send-region-or-buffer
            :before (lambda (&optional rest)
                      (let ((curbuf (current-buffer)))
                        (elpy-shell-switch-to-shell)
                        (goto-char (point-max))
                        (recenter -10)
                        (elpy-shell-switch-to-buffer)))
            '((name . "elpy-shell-scroll-to-bottom")))
(set-face-bold-p 'bold nil)
(mapc ;; remove all bold
 (lambda (face)
   (set-face-attribute face
                       nil ;; all frames
                       :weight 'normal))
 (face-list))

;;(add-hook 'python-mode-hook 'jedi:setup)
;;(setq jedi:complete-on-dot t)   
