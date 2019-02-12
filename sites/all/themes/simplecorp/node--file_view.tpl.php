<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> hentry clearfix"<?php print $attributes; ?>>
     <div class="entry-body clearfix">
        <div class="content"<?php print $content_attributes; ?>>
        <?php // We hide the comments and links now so that we can render them later.
        hide($content['comments']);
        hide($content['links']);
        print render($content); ?>
        </div>
        <?php print render($content['links']); ?>
    </div>
</article>
